#pragma once

#include "Ped.h"
#include <cassert>
#include <unordered_map>

class CPedGrid
{
public:

	typedef std::unordered_multimap<s32, const CPed*> TPedMap;

	CPedGrid(float cellSize)
		: m_cellSize(cellSize)
		, m_cellDiagonal(sqrt(2.0f * cellSize))
	{ /* ... */ }

	float GetCellSize() const { return m_cellSize; }
	float GetCellDiagonal() const { return m_cellDiagonal; }

	CPedGrid& operator=(const CPedGrid&) = delete;

	void RegisterPed(const CPed* pPed)
	{
		const s32 hash = CalculateHash(pPed->GetTransform().Position);
		m_pedMap.insert(std::make_pair(hash, pPed));
	}

	void UnregisterPed(const CPed* pPed)
	{
		const s32 hash = CalculateHash(pPed->GetTransform().Position);

		std::pair<TPedMap::iterator, TPedMap::iterator> range = m_pedMap.equal_range(hash);
		for (TPedMap::iterator itPed = range.first; itPed != range.second; ++itPed)
		{
			if (itPed->second == pPed)
			{
				m_pedMap.erase(itPed);
				break;
			}
		}
	}

	std::pair<TPedMap::iterator, TPedMap::iterator> GetPedsAt(const Point2s16& indexes)
	{
		return m_pedMap.equal_range(CalculateHash(indexes));
	}

	void UpdatePed(const CPed* pPed, const Point2f& prevPos, const Point2f& newPos)
	{
		const s32 prevHash = CalculateHash(prevPos);
		const s32 newHash = CalculateHash(newPos);

		if (prevHash != newHash)
		{
			std::pair<TPedMap::iterator, TPedMap::iterator> range = m_pedMap.equal_range(prevHash);
			for (TPedMap::iterator itPed = range.first; itPed != range.second; ++itPed)
			{
				if (itPed->second == pPed)
				{
					m_pedMap.erase(itPed);
					break;
				}
			}

			m_pedMap.insert(std::make_pair(newHash, pPed));
		}
	}

	Point2s16 GetCellIndexes(const Point2f& position)
	{
		const s32 iRow = static_cast<int>(position[1] / m_cellSize);
		const s32 iColumn = static_cast<int>(position[0] / m_cellSize);
		assert(
			iRow >= std::numeric_limits<s16>::min() && iRow <= std::numeric_limits<s16>::max() &&
			iColumn >= std::numeric_limits<s16>::min() && iColumn <= std::numeric_limits<s16>::max()
			);
		return Point2s16(static_cast<s16>(iColumn), static_cast<s16>(iRow));
	}

private:

	s32 CalculateHash(const Point2f& position)
	{
		const Point2s16 cellIndexes = GetCellIndexes(position);
		return CalculateHash(cellIndexes);
	}

	s32 CalculateHash(const Point2s16& cellIndexes)
	{
		return (cellIndexes[0] << 16) + cellIndexes[1];
	}

	const float m_cellSize;
	const float m_cellDiagonal;

	TPedMap m_pedMap;
};
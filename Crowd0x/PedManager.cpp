#include "PedManager.h"
#include "PedGrid.h"
#include "Ped.h"
#include "Types.h"
#include "Transform.h"
#include "DrawService.h"
#include <array>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>

namespace PedManager
{

namespace // internal
{

const float PED_DEFAULT_MASS = 1.0f;

const u16 MAX_NUM_PEDS = 1024;
std::array<CPed, MAX_NUM_PEDS> s_Peds;

// Grid
// TODO[egarcia]: REVIEW! dynamic memory
CPedGrid s_Grid(0.1f);

} // internal

void Init()
{
	std::random_device rd;
	std::mt19937 mtgen(rd());
	std::uniform_real_distribution<float> ndpos(0.0f, 1.0f);
	std::uniform_real_distribution<float> ndangle(0.0f, cml::constantsf::two_pi());

	for (CPed& ped : s_Peds)
	{
		ped = CPed{ STransform{ Point2f{ ndpos(mtgen), ndpos(mtgen) }, ndangle(mtgen) }, PED_DEFAULT_MASS };
		s_Grid.RegisterPed(&ped);
	}
}


void Done()
{
	for (CPed& ped : s_Peds)
	{
		s_Grid.UnregisterPed(&ped);
	}
}

void Update(float fTimeDelta)
{
	// Execute
	for (CPed& ped : s_Peds)
	{
		ped.UpdateExecute(fTimeDelta);
	}

	// Commit
	for (CPed& ped : s_Peds)
	{
		Point2f vPrevPos = ped.GetTransform().Position;
		ped.UpdateCommit();
		s_Grid.UpdatePed(&ped, vPrevPos, ped.GetTransform().Position);
	}

}

void Draw()
{
	for (const CPed& ped : s_Peds)
	{
		ped.Draw();
	}

	//DrawService::DrawCircle(Point2f{ 0.5f, 0.5f }, 0.2f, 0x0000FFFF);
}

// TODO[egarcia]: Move to grid class?
std::vector<const CPed*> GetPedsAtDistance(const Point2f& position, float distance)
{
	std::vector<const CPed*> peds;

	const float distance2 = distance * distance;

	//for (CPed& ped : s_Peds)
	//{
	//	if ((ped.GetTransform().Position - position).length_squared() < distance2)
	//	{
	//		peds.push_back(&ped);
	//	}
	//}

	const Point2s16 pedCellIndexes = s_Grid.GetCellIndexes(position);

	//const s16 insideCellDistance = static_cast<s16>(distance / s_Grid.GetCellDiagonal()) - 1;
	//const Point2s16 insideCellMin { pedCellIndexes[0] - insideCellDistance, pedCellIndexes[1] - insideCellDistance };
	//const Point2s16 insideCellMax { pedCellIndexes[0] + insideCellDistance, pedCellIndexes[1] + insideCellDistance };

	const s16 maxCellDistance = static_cast<s16>(ceil(distance / s_Grid.GetCellSize()));

	const s16 iMinCellX = pedCellIndexes[0] - maxCellDistance;
	const s16 iMaxCellX = pedCellIndexes[0] + maxCellDistance;
	const s16 iMinCellY = pedCellIndexes[1] - maxCellDistance;
	const s16 iMaxCellY = pedCellIndexes[1] + maxCellDistance;

	for (s16 iCellX = iMinCellX; iCellX <= iMaxCellX; ++iCellX)
	{
		for (s16 iCellY = iMinCellY; iCellY <= iMaxCellY; ++iCellY)
		{
			//const bool bCellInside = (iCellX >= insideCellMin[0]) && (iCellX <= insideCellMax[0]) && (iCellY >= insideCellMin[1]) && (iCellY <= insideCellMax[1]);

			std::pair<CPedGrid::TPedMap::iterator, CPedGrid::TPedMap::iterator> pedsRange = s_Grid.GetPedsAt(Point2s16(iCellX, iCellY));
			for (CPedGrid::TPedMap::iterator itPed = pedsRange.first; itPed != pedsRange.second; ++itPed)
			{
				if (/*bCellInside || */(itPed->second->GetTransform().Position - position).length_squared() < distance2)
				{
					peds.push_back(itPed->second);
				}
			}
		}
	}

	return peds;
}

} // namespace PedManager


#include "Ped.h"
#include "PedManager.h"
#include "DrawService.h"
#include "MathUtils.h"
#include <functional>

CPed::CPed() = default;

CPed::CPed(CPed&& ped)
	: m_transform(std::move(ped.m_transform))
	, m_mass(std::move(ped.m_mass))
	, m_locomotion(std::move(ped.m_locomotion))
	, m_steering(std::move(ped.m_steering))
{

}

const CPed& CPed::operator=(CPed&& ped)
{
	if (this != &ped)
	{ 
		m_transform = std::move(ped.m_transform);
		m_mass = std::move(ped.m_mass);
		m_locomotion = std::move(ped.m_locomotion);
		m_steering = std::move(ped.m_steering);
	}

	return *this;
}

CPed::CPed(STransform const& transform, float mass)
	: m_transform(transform)
	, m_mass(mass)
{

}

void CPed::UpdateExecute(float timeStep)
{
	m_steering.UpdateExecute(*this, timeStep);
	m_locomotion.UpdateExecute(*this, timeStep);
}

void CPed::UpdateCommit()
{
	m_steering.UpdateCommit(*this);
	m_locomotion.UpdateCommit(*this);
}

void CPed::Draw() const
{
	//std::vector<const CPed*> peds = PedManager::GetPedsAtDistance(Point2f{ 0.5f, 0.5f }, 0.2f);
	//const u32 color = std::find(peds.begin(), peds.end(), this) != peds.end() ? 0xFF0000FF : 0xFFFFFFFF;
	
	const u32 color = 0xFF0000FF;
	DrawService::DrawTriangle(m_transform, 0.025f, 0.01f, color);
}
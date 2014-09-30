#pragma once

#include "PedLocomotion.h"
#include "PedSteering.h"
#include "Types.h"
#include "Transform.h"

class CPed
{
public:

	CPed();
	CPed(STransform const& transform, float mass);

	CPed(CPed const& ped) = delete;
	const CPed& operator=(CPed const& ped) = delete;

	CPed(CPed&& ped);
	const CPed& operator=(CPed&& ped);
	
	void UpdateExecute(float timeStep);
	void UpdateCommit();

	STransform& GetTransform() { return m_transform; }
	STransform const& GetTransform() const { return m_transform; }

	CPedSteering& GetSteering() { return m_steering; }
	CPedLocomotion& GetLocomotion() { return m_locomotion; }

	float GetMass() const { return m_mass; }

	void Draw() const;

private:

	STransform m_transform;
	float m_mass;

	// Components
	CPedSteering m_steering;
	CPedLocomotion m_locomotion;
};
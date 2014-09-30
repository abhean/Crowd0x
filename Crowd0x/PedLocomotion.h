#pragma once

#include "PedComponent.h"
#include "Types.h"

class CPed;

class CPedLocomotion : public CPedComponent
{
public:

	CPedLocomotion();

	CPedLocomotion(const CPedLocomotion&) = delete;
	CPedLocomotion& operator=(const CPedLocomotion&) = delete;

	CPedLocomotion(CPedLocomotion&&);
	CPedLocomotion& operator=(CPedLocomotion&&);

	void UpdateExecute(CPed& ped, float timeStep) override;
	void UpdateCommit(CPed& ped) override;

	void ApplyImpulse(const Vec2f& impulse);

private:

	typedef CPedComponent Super;

	void ApplyTickAccImpulse(const CPed& ped);
	void ApplyAcceleration(float timeDelta);
	void ApplyVelocity(CPed& ped, float timeDelta);

	Vec2f m_tickAccImpulse;
	Vec2f m_acceleration;
	Vec2f m_velocity;

	// Commit pending
	Vec2f m_nextPosition;
	float m_nextRotation;
};
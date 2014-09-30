#include "PedLocomotion.h"
#include "Ped.h"
#include "MathUtils.h"

namespace // constants 
{

const float MAX_IMPULSE_PER_TICK = 10.0f;
const float MAX_SPEED = 10.0f;
const float fMIN_SPEED_TO_CHANGE_HEADING = 0.001f;

}

CPedLocomotion::CPedLocomotion()
	: m_velocity(0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f)
	, m_tickAccImpulse(0.0f, 0.0f)
	, m_nextPosition(0.0f, 0.0f)
	, m_nextRotation(0.0f)
{

}

CPedLocomotion::CPedLocomotion(CPedLocomotion&& pedLocomotion)
	: m_velocity(std::move(pedLocomotion.m_velocity))
	, m_acceleration(std::move(pedLocomotion.m_acceleration))
	, m_tickAccImpulse(std::move(pedLocomotion.m_tickAccImpulse))
	, m_nextPosition(std::move(pedLocomotion.m_nextPosition))
	, m_nextRotation(std::move(pedLocomotion.m_nextRotation))
{
}

CPedLocomotion & CPedLocomotion::operator=(CPedLocomotion&& pedLocomotion)
{
	if (this != &pedLocomotion)
	{
		m_velocity = std::move(pedLocomotion.m_velocity);
		m_acceleration = std::move(pedLocomotion.m_acceleration);
		m_tickAccImpulse = std::move(pedLocomotion.m_tickAccImpulse);
		m_nextPosition = std::move(pedLocomotion.m_nextPosition);
		m_nextRotation = std::move(pedLocomotion.m_nextRotation);
	}

	return *this;
}

void CPedLocomotion::UpdateExecute(CPed& ped, float timeDelta)
{
	Super::UpdateExecute(ped, timeDelta);

	ApplyTickAccImpulse(ped);

	ApplyAcceleration(timeDelta);

	ApplyVelocity(ped, timeDelta);
}

void CPedLocomotion::UpdateCommit(CPed& ped)
{
	Super::UpdateCommit(ped);

	STransform& transform = ped.GetTransform();
	transform.Position = m_nextPosition;
	transform.Rotation = m_nextRotation;
}

void CPedLocomotion::ApplyImpulse(const Vec2f& impulse)
{
	m_tickAccImpulse += impulse;
}

void CPedLocomotion::ApplyTickAccImpulse(const CPed& ped)
{
	m_acceleration = GetTruncated(m_tickAccImpulse, MAX_IMPULSE_PER_TICK) / ped.GetMass();
	m_tickAccImpulse.zero();
}

void CPedLocomotion::ApplyAcceleration(float timeDelta)
{
	m_velocity = GetTruncated(m_velocity + m_acceleration * timeDelta, MAX_SPEED);
}

void CPedLocomotion::ApplyVelocity(CPed& ped, float timeDelta)
{
	STransform& transform = ped.GetTransform();
	m_nextPosition = transform.Position + m_velocity * timeDelta;

	float speed = m_velocity.length();
	if (speed > fMIN_SPEED_TO_CHANGE_HEADING)
	{
		Vec2f velDir = m_velocity / speed;
		m_nextRotation = atan2(-velDir[0], velDir[1]);
	}
	else
	{
		m_nextRotation = transform.Rotation;
	}
}

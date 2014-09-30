#include "PedSteering.h"
#include "Ped.h"
#include "PedLocomotion.h"
#include "PedManager.h"

CPedSteering::CPedSteering()
{
}

//CPedSteering::CPedSteering(CPedSteering&& /*pedSteering*/)
//{
//}

void CPedSteering::UpdateExecute(CPed& ped, float timeStep)
{
	Super::UpdateExecute(ped, timeStep);

	std::vector<const CPed*> nearbyPeds = PedManager::GetPedsAtDistance(ped.GetTransform().Position, 0.1f);
	for (const CPed* pPed : nearbyPeds)
	{
		if (pPed != &ped)
		{
			const Vec2f toPed = pPed->GetTransform().Position - ped.GetTransform().Position;
			const float distance = toPed.length();
			if (distance > 0.0f)
			{
				ped.GetLocomotion().ApplyImpulse(toPed / distance * 0.00001f);
			}
		}
	}
}

void CPedSteering::UpdateCommit(CPed& ped) 
{
	Super::UpdateCommit(ped);

}

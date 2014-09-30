#include "PedPerception.h"

CPedPerception::CPedPerception()
{
}

CPedPerception::CPedPerception(CPedPerception&& /*pedPerception*/)
{
}

void CPedPerception::UpdateExecute(CPed& ped, float timeStep)
{
	Super::UpdateExecute(ped, timeStep);


}

void CPedPerception::UpdateCommit(CPed& ped)
{
	Super::UpdateCommit(ped);


}

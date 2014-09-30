#pragma once

#include "PedComponent.h"

class CPed;

class CPedPerception : public CPedComponent
{
public:

	CPedPerception();
	CPedPerception(CPedPerception&& pedPerception);

	void UpdateExecute(CPed& ped, float timeStep) override;
	void UpdateCommit(CPed& ped) override;

private:

	typedef CPedComponent Super;

};
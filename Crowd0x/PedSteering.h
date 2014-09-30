#pragma once

#include "PedComponent.h"
#include "Types.h"

class CPed;

class CPedSteering : public CPedComponent
{
public:

	CPedSteering();
	
	CPedSteering(const CPedSteering&) = delete;
	CPedSteering& operator=(const CPedSteering&) = delete;

	CPedSteering(CPedSteering&&) = default;
	CPedSteering& operator=(CPedSteering&&) = default;

	void UpdateExecute(CPed& ped, float timeStep) override;
	void UpdateCommit(CPed& ped) override;

private:

	typedef CPedComponent Super;

};
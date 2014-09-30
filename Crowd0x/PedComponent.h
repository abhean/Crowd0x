#pragma once

class CPed;

class CPedComponent
{
public:

	CPedComponent()
	{ /* ... */ }

	CPedComponent(const CPedComponent&) = delete;
	const CPedComponent& operator=(const CPedComponent&) = delete;
	
	CPedComponent(CPedComponent&&) = default;
	CPedComponent& operator=(CPedComponent&&) = default;

	virtual void UpdateExecute(CPed& /*ped*/, float /*timeStep*/) { /* ... */ }
	virtual void UpdateCommit(CPed& /*ped*/) { /* ... */ }

private:

};
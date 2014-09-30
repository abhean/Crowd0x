#pragma once

#include "Types.h"
#include <vector>

class CPed;

namespace PedManager
{

void Init();
void Done();

void Update(float timeDelta);
void Draw();

std::vector<const CPed*> GetPedsAtDistance(const Point2f& position, float fDistance);

} // PedManager
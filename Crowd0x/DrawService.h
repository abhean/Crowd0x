#pragma once

#include "Types.h"
#include "Transform.h"

namespace DrawService
{

int Init();
void Done();

void ProcessEvents();

void RenderClear();
void RenderPresent();

void DrawTriangle(const STransform& transform, float height, float base, u32 color);
void DrawCircle(const Point2f& position, float radius, u32 color);

} // DrawService
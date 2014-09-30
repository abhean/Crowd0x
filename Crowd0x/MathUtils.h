#pragma once

#include "Types.h"

inline Vec2f GetTruncated(const Vec2f v, const float max)
{
	Vec2f result{0.0f, 0.0f};

	if (max > 0.0f)
	{
		result = v;

		float magnitude = v.length();
		if (magnitude > max)
		{
			result *= (max / magnitude);
		}
	}

	return result;
}


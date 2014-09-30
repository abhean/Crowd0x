#pragma once

#pragma warning( push )
#pragma warning( disable : 4512)
#include "cml/cml.h"
#pragma warning( pop ) 



using u8 = unsigned char;
using s8 = char;

using u16 = unsigned short;
using s16 = short;

using u32 = unsigned int;
using s32 = int;

using Point2f = cml::vector< float, cml::fixed<2> >;
using Vec2f   = cml::vector< float, cml::fixed<2> >;

using Point3f = cml::vector< float, cml::fixed<3> >;
using Vec3f   = cml::vector< float, cml::fixed<3> >;

using Point2s16 = cml::vector< s16, cml::fixed<2> >;
using Vec2s16   = cml::vector< s16, cml::fixed<2> >;

using Point3s16 = cml::vector< s16, cml::fixed<3> >;
using Vec3s16   = cml::vector< s16, cml::fixed<3> >;

using Point2s32 = cml::vector< s32, cml::fixed<2> >;
using Vec2s32   = cml::vector< s32, cml::fixed<2> >;

using Point3s32 = cml::vector< s32, cml::fixed<3> >;
using Vec3s32   = cml::vector< s32, cml::fixed<3> >;

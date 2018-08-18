#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>

using namespace entityx;

namespace px
{
	namespace utils
	{
		struct Collision
		{
			explicit Collision(Entity left, Entity right) : left(left), right(right) {}

			Entity left, right;
		};
	}
}
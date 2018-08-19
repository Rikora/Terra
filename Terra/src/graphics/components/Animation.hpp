#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/AnimationHelper.hpp>

namespace px
{
	struct Animation
	{
		Animation() : animations(std::make_unique<utils::AnimationHelper>())  {}

		std::unique_ptr<utils::AnimationHelper> animations;
	};
}
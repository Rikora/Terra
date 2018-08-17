#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>
#include <Thor/Animations/FrameAnimation.hpp>

namespace px
{
	struct Animation
	{
		explicit Animation() : animator(animations) {}

		AnimationsHolder animations;
		Animator animator;
		std::vector<thor::FrameAnimation> frameAnimations;
	};
}
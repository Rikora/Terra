#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Thor/Animations/FrameAnimation.hpp>
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>

namespace px
{
	namespace utils
	{
		class AnimationHelper
		{
		public:
			AnimationHelper();
			~AnimationHelper() = default;

		public:
			void addAnimation(const std::string & id, int row, int frames, sf::Time duration = sf::seconds(1.f));
			void playAnimation(const std::string & id, bool repeat = false);
			void update();
			void animate(sf::Sprite & sprite);

		private:
			thor::FrameAnimation addFrames(thor::FrameAnimation & anim, int row, int frames, int pxSize = 64, float duration = 1.f);

		private:
			AnimationsHolder m_animations;
			Animator m_animator;
			sf::Clock m_animationClock;
		};
	}
}

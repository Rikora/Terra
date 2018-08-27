#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Thor/Animations/Animator.hpp>
#include <Thor/Animations/FrameAnimation.hpp>
#include <SFML/System/Clock.hpp>

namespace px
{
	class SpriteAnimation
	{
	public:
		SpriteAnimation() : m_animator(m_animations) {};
		~SpriteAnimation() = default;

	public:
		inline void addAnimation(const std::string & id, int row, int frames, sf::Time duration = sf::seconds(1.f))
		{
			thor::FrameAnimation frameAnim;
			m_animations.addAnimation(id, addFrames(frameAnim, row, frames), duration);
		}

		inline void playAnimation(const std::string & id, bool repeat = false)
		{
			repeat ? m_animator.play() << id << thor::Playback::loop(id) : m_animator.play();
		}

		inline void update()
		{
			m_animator.update(m_animationClock.restart());
		}

		inline void animate(sf::Sprite & sprite)
		{
			m_animator.animate(sprite);
		}

	private:
		inline thor::FrameAnimation addFrames(thor::FrameAnimation & anim, int row, int frames, int pxSize = 64, float duration = 1.f)
		{
			if (frames > 1)
				for (int i = 0; i < frames * pxSize; i += pxSize)
					anim.addFrame(duration, sf::IntRect(i, row * pxSize, pxSize, pxSize));
			else
				anim.addFrame(duration, sf::IntRect(0, row * pxSize, pxSize, pxSize));

			return anim;
		}

	private:
		using AnimationsHolder = thor::AnimationMap<sf::Sprite, std::string>;
		using Animator = thor::Animator<sf::Sprite, std::string>;

	private:
		AnimationsHolder m_animations;
		Animator m_animator;
		sf::Clock m_animationClock;
	};


	struct Animation
	{
		Animation() : animations(std::make_unique<SpriteAnimation>())  {}

		std::unique_ptr<SpriteAnimation> animations;
	};
}
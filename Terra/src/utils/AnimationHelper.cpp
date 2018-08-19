////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/AnimationHelper.hpp>

namespace px
{
	namespace utils
	{
		AnimationHelper::AnimationHelper() : m_animator(m_animations)
		{
		}

		void AnimationHelper::addAnimation(Animations::ID id, int row, int frames, sf::Time duration)
		{
			thor::FrameAnimation frameAnim;
			m_animations.addAnimation(id, addFrames(frameAnim, row, frames), duration);
		}

		void AnimationHelper::playAnimation(Animations::ID id, bool repeat)
		{
			repeat ? m_animator.play() << id << thor::Playback::loop(id) : m_animator.play();
		}

		void AnimationHelper::update()
		{
			m_animator.update(m_animationClock.restart());
		}

		void AnimationHelper::animate(sf::Sprite & sprite)
		{
			m_animator.animate(sprite);
		}

		thor::FrameAnimation AnimationHelper::addFrames(thor::FrameAnimation & anim, int row, int frames, int pxSize, float duration)
		{
			if (frames > 1)
				for (int i = 0; i < frames * pxSize; i += pxSize)
					anim.addFrame(duration, sf::IntRect(i, row * pxSize, pxSize, pxSize));
			else
				anim.addFrame(duration, sf::IntRect(0, row * pxSize, pxSize, pxSize));

			return anim;
		}
	}	
}
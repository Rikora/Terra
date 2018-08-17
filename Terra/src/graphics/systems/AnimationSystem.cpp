////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/Clock.hpp>
#include <graphics/systems/AnimationSystem.hpp>
#include <graphics/components/Render.hpp>
#include <graphics/components/Animation.hpp>

namespace px
{
	AnimationSystem::AnimationSystem(sf::Clock & animationClock) : m_animationClock(animationClock)
	{
	}

	void AnimationSystem::update(EntityManager & es, EventManager & events, TimeDelta dt)
	{
		ComponentHandle<Render> render;
		ComponentHandle<Animation> anim;

		for (auto entity : es.entities_with_components(render, anim))
		{
			anim->animator.update(m_animationClock.restart());
			anim->animator.animate(*render->sprite);
		}
	}
}
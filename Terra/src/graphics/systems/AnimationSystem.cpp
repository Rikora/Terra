////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/systems/AnimationSystem.hpp>
#include <graphics/components/Render.hpp>
#include <graphics/components/Animation.hpp>

namespace px
{
	AnimationSystem::AnimationSystem()
	{
	}

	void AnimationSystem::update(EntityManager & es, EventManager & events, TimeDelta dt)
	{
		ComponentHandle<Render> render;
		ComponentHandle<Animation> anim;

		for (auto entity : es.entities_with_components(render, anim))
		{
			anim->animator.update(anim->animationClock.restart());
			anim->animator.animate(*render->sprite);
		}
	}
}
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/systems/AnimationSystem.hpp>
#include <graphics/components/Render.hpp>
#include <graphics/components/Animation.hpp>

namespace px
{
	void AnimationSystem::update(EntityManager & es, EventManager & events, TimeDelta dt)
	{
		ComponentHandle<Render> render;
		ComponentHandle<Animation> anim;

		for (auto entity : es.entities_with_components(render, anim))
		{
			anim->animations->update();
			anim->animations->animate(*render->sprite);
		}
	}
}
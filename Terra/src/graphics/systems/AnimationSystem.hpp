#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <graphics/components/Render.hpp>
#include <graphics/components/Animation.hpp>

using namespace entityx;

namespace px
{
	class AnimationSystem : public System<AnimationSystem>
	{
	public:
		inline virtual void update(EntityManager & es, EventManager & events, TimeDelta dt) override
		{
			ComponentHandle<Render> render;
			ComponentHandle<Animation> anim;

			for (auto entity : es.entities_with_components(render, anim))
			{
				anim->animations->update();
				anim->animations->animate(*render->sprite);
			}
		}
	};
}
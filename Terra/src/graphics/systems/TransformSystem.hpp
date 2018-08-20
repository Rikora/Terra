#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <graphics/components/Render.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/BoundingBox.hpp>

using namespace entityx;

namespace px
{
	class TransformSystem : public System<TransformSystem>
	{
	public:
		virtual void update(EntityManager & es, EventManager & events, TimeDelta dt) override
		{
			ComponentHandle<Render> render;
			ComponentHandle<Transform> trans;

			for (auto entity : es.entities_with_components(render, trans))
			{
				render->sprite->setPosition(trans->position);

				// Set the position of the bounding box
				if (entity.has_component<BoundingBox>())
				{
					auto box = entity.component<BoundingBox>();
					box->boundingBox.left = trans->position.x;
					box->boundingBox.top = trans->position.y;
				}
			}
		}
	};
}
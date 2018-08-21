#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <graphics/components/BoundingBox.hpp>
#include <graphics/components/Minion.hpp>
#include <utils/Collision.hpp>

using namespace entityx;

namespace px
{
	class CollisionSystem : public System<CollisionSystem>
	{
	public:
		virtual void update(EntityManager & es, EventManager & events, TimeDelta dt) override
		{
			// TODO: change this later for only box components?
			ComponentHandle<Minion> left_box;
			ComponentHandle<BoundingBox> right_box;

			for (auto left_entity : es.entities_with_components(left_box))
			{
				for (auto right_entity : es.entities_with_components(right_box))
				{
					if (left_entity == right_entity) continue; // Avoid self collisions

					if (right_box->boundingBox.contains(left_box->minion->getFrontCollider()))
						events.emit<utils::Collision>(left_entity, right_entity);
				}
			}
		}
	};
}
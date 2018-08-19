////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/systems/CollisionSystem.hpp>
#include <graphics/components/BoundingBox.hpp>
#include <utils/Collision.hpp>

namespace px
{
	CollisionSystem::CollisionSystem()
	{
	}

	void CollisionSystem::update(EntityManager & es, EventManager & events, TimeDelta dt)
	{
		ComponentHandle<BoundingBox> left_box, right_box;

		for (auto left_entity : es.entities_with_components(left_box))
		{
			for (auto right_entity : es.entities_with_components(right_box))
			{
				if (left_entity == right_entity) continue; // Avoid self collisions

				if (left_box->boundingBox.intersects(right_box->boundingBox))
					events.emit<utils::Collision>(left_entity, right_entity);
			}
		}
	}
}
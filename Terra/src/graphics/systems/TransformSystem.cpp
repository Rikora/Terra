#include <graphics/systems/TransformSystem.hpp>
#include <graphics/components/Render.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/BoundingBox.hpp>

namespace px
{
	void TransformSystem::update(EntityManager & es, EventManager & events, TimeDelta dt)
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
}
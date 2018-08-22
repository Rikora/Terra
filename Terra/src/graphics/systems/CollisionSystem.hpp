#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <graphics/components/BoundingBox.hpp>
#include <graphics/components/Minion.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/Render.hpp>

using namespace entityx;

namespace px
{
	class CollisionSystem : public System<CollisionSystem>
	{
	public:
		virtual void update(EntityManager & es, EventManager & events, TimeDelta dt) override
		{
			ComponentHandle<Minion> minion, left_minion, right_minion;

			for (auto m : es.entities_with_components(minion))
				minion->minion->attack(m, dt);

			for (auto left_entity : es.entities_with_components(left_minion))
			{
				for (auto right_entity : es.entities_with_components(right_minion))
				{
					if (left_entity == right_entity) continue; // Avoid self collisions

					if (right_entity.component<BoundingBox>()->boundingBox.contains(left_minion->minion->getFrontCollider()))
					{
						auto haltMinion = [left_minion, right_minion](Entity & left_entity)
						{
							if (right_minion->minion->isAttacking() || right_minion->minion->isFrontAttacking())
							{
								left_minion->minion->setVelocity(0.f);
								left_entity.component<Animation>()->animations->playAnimation("idle", true);
								left_minion->minion->setFrontAttacking(true);
							}
						};

						auto attackMinion = [left_minion, right_minion](Entity & left_entity)
						{
							if (!left_minion->minion->isAttacking())
							{
								left_minion->minion->setVelocity(0.f);
								left_entity.component<Animation>()->animations->playAnimation("attack", true);
								left_minion->minion->setAttacking(true);
							}
						};

						// Different minion types are situated in opposite directions
						if ((left_entity.component<Transform>()->position.x < right_entity.component<Transform>()->position.x) &&
							(left_entity.component<Render>()->name == "Player" && right_entity.component<Render>()->name == "Player"))
						{
							haltMinion(left_entity);
						}
						else if ((left_entity.component<Transform>()->position.x > right_entity.component<Transform>()->position.x) &&
								(left_entity.component<Render>()->name == "Enemy" && right_entity.component<Render>()->name == "Enemy"))
						{
							haltMinion(left_entity);
						}
						else if ((left_entity.component<Transform>()->position.x < right_entity.component<Transform>()->position.x) &&
								(left_entity.component<Render>()->name == "Player" && right_entity.component<Render>()->name == "Enemy"))
						{
							attackMinion(left_entity);
						}
						else if ((left_entity.component<Transform>()->position.x > right_entity.component<Transform>()->position.x) &&
								(left_entity.component<Render>()->name == "Enemy" && right_entity.component<Render>()->name == "Player"))
						{
							attackMinion(left_entity);
						}
					}
				}
			}
		}
	};
}
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
			{
				// Deal damage at the correct frame
				if (minion->minion->isAttacking())
				{
					if (minion->minion->getTarget())
					{
						if (m.component<Render>()->name == "Player")
						{
							if (minion->minion->m_damageWatch.isRunning() && minion->minion->m_damageWatch.getElapsedTime().asSeconds() >= 0.65f)
							{
								auto target = minion->minion->getTarget().component<Minion>();
								target->minion->setHealth(target->minion->getHealth() - 1);
								std::cout << target->minion->getHealth() << std::endl;
								minion->minion->m_damageWatch.restart();
							}
						}
					}
					else
					{
						minion->minion->m_damageWatch.reset();
						minion->minion->resetVelocity();
						m.component<Animation>()->animations->playAnimation("walk", true);
						minion->minion->setAttacking(false);
						minion->minion->setFrontAttacking(false);
					}
				}

				minion->minion->update(m, dt);
			}

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
								// Minion goes back to idle (first frame) by default? Makes no sence but this works for the moment...
								left_minion->minion->setVelocity(0.f);
								left_entity.component<Animation>()->animations->playAnimation("walk", true);
								left_minion->minion->setFrontAttacking(true);
							}
							else
							{
								left_minion->minion->resetVelocity();
								left_minion->minion->setFrontAttacking(false);
							}
						};

						auto attackMinion = [left_minion, right_minion](Entity & left_entity, Entity & right_entity)
						{
							if (!left_minion->minion->isAttacking())
							{
								left_minion->minion->setVelocity(0.f);
								left_entity.component<Animation>()->animations->playAnimation("attack", true);
								left_minion->minion->setTarget(right_entity);
								left_minion->minion->setAttacking(true);
								left_minion->minion->m_damageWatch.start();
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
							attackMinion(left_entity, right_entity);
						}
						else if ((left_entity.component<Transform>()->position.x > right_entity.component<Transform>()->position.x) &&
								(left_entity.component<Render>()->name == "Enemy" && right_entity.component<Render>()->name == "Player"))
						{
							attackMinion(left_entity, right_entity);
						}
					}
				}
			}
		}
	};
}
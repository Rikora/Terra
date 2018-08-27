#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <graphics/components/BoundingBox.hpp>
#include <graphics/components/Minion.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/Render.hpp>
#include <graphics/components/Healthbar.hpp>
#include <graphics/components/TextAnimation.hpp>
#include <utils/GameManager.hpp>

using namespace entityx;

namespace px
{
	class CollisionSystem : public System<CollisionSystem>
	{
	public:
		explicit CollisionSystem(Scene & scene, utils::GameManager & gameManager) : m_scene(scene), m_gameManager(gameManager) {}

		inline virtual void update(EntityManager & es, EventManager & events, TimeDelta dt) override
		{
			ComponentHandle<Minion> minion, left_minion, right_minion;

			for (auto m : es.entities_with_components(minion))
			{
				// Deal damage at the correct frame
				if (minion->minion->isAttacking())
				{
					if (minion->minion->getTarget())
					{
						auto dealDamage = [minion](const float & attackFrame)
						{
							// Reduce health of target minion and display result as the health bar
							if (minion->minion->m_damageWatch.isRunning() && minion->minion->m_damageWatch.getElapsedTime().asSeconds() >= attackFrame)
							{
								auto target = minion->minion->getTarget().component<Minion>();
								auto healthbar = minion->minion->getTarget().component<Healthbar>();
								target->minion->setHealth(target->minion->getHealth() - minion->minion->getDamage());
								healthbar->bar.component<Transform>()->scale.x = ((float)target->minion->getHealth() / (float)target->minion->getMaxHealth()) * 
																			     healthbar->healthScaleX;
								minion->minion->m_damageWatch.restart();
							}
						};

						if (minion->minion->getType() == "Monk")
							dealDamage(0.65f);
						else if (minion->minion->getType() == "SpearOrc")
							dealDamage(0.65f);
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

				updateMinion(m, dt);
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

						auto attackMinion = [left_minion](Entity & left_entity, Entity & right_entity)
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

		private:
			inline void updateMinion(Entity & entity, double dt)
			{
				auto minion = entity.component<Minion>();
				auto trans = entity.component<Transform>();
				auto healthbar = entity.component<Healthbar>();
				auto render = entity.component<Render>();
				auto box = entity.component<BoundingBox>();

				// Move the minion and healthbars
				trans->position.x += minion->minion->getVelocity() * (float)dt;
				healthbar->background.component<Transform>()->position = trans->position + healthbar->backgroundOffset;
				healthbar->bar.component<Transform>()->position = trans->position + healthbar->barOffset;

				if (minion->minion->getTarget() == NULL)
					minion->minion->resetVelocity();

				// Destroy minion and spawn resource value text only for enemies
				if (minion->minion->getHealth() <= 0)
				{
					sf::Vector2f pos = sf::Vector2f(box->boundingBox.left, box->boundingBox.top);
					std::string name = render->name;
					uint value = m_gameManager.convertResourceType(minion->minion->getType());
					healthbar->background.destroy();
					healthbar->bar.destroy();
					entity.destroy();

					if (name == "Enemy")
					{
						m_gameManager.playerGold += value;
						auto text = m_scene.createText("+" + std::to_string(value), Fonts::Game, 16, pos, sf::Color::Yellow);
						text.assign<TextAnimation>(45.f, 3);
					}
				}
			}

		private:
			Scene & m_scene;
			utils::GameManager & m_gameManager;
	};
}
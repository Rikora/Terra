#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/Collision.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/Animation.hpp>
#include <graphics/components/Render.hpp>
#include <graphics/components/Minion.hpp>
#include <array>

using namespace entityx;

namespace px
{
	class MinionSystem : public System<MinionSystem>, public Receiver<MinionSystem>
	{
	public:
		virtual void configure(EventManager & event_manager) override { event_manager.subscribe<utils::Collision>(*this); }

		virtual void update(EntityManager & es, EventManager & events, TimeDelta dt) override
		{
			ComponentHandle<Minion> minion, left_minion, right_minion;

			for (auto m : es.entities_with_components(minion))
				minion->minion->attack(m);

			if (m_colliders[0] != NULL && m_colliders[1] != NULL)
			{
				for (auto left_entity : es.entities_with_components(left_minion))
				{
					for (auto right_entity : es.entities_with_components(right_minion))
					{
						if (left_entity == right_entity) continue;

						auto haltMinion = [&left_entity, right_entity, left_minion, right_minion](Entity collider_1, Entity collider_2)
						{
							if ((left_entity == collider_1) && (right_entity == collider_2 && right_minion->minion->isAttacking()) ||
								(left_entity == collider_1) && (right_entity == collider_2 && right_minion->minion->isFrontAttacking()))
							{
								// Halt the minion behind
								left_minion->minion->setVelocity(0.f);
								left_entity.component<Animation>()->animations->playAnimation("idle", true);
								left_minion->minion->setFrontAttacking(true);
							}
						};

						// Different minion types are situated in opposite directions
						if ((m_colliders[0].component<Transform>()->position.x < m_colliders[1].component<Transform>()->position.x) &&
							(m_colliders[0].component<Render>()->name == "Player" && m_colliders[1].component<Render>()->name == "Player"))
						{
							haltMinion(m_colliders[0], m_colliders[1]);
						}
						else if ((m_colliders[0].component<Transform>()->position.x > m_colliders[1].component<Transform>()->position.x) &&
								(m_colliders[0].component<Render>()->name == "Enemy" && m_colliders[1].component<Render>()->name == "Enemy"))
						{
							haltMinion(m_colliders[0], m_colliders[1]);
						}	
					}
				}
			}
		}

		virtual void receive(const utils::Collision & collision) { m_colliders = { collision.left, collision.right }; }

	private:
		std::array<Entity, 2> m_colliders;
	};
}
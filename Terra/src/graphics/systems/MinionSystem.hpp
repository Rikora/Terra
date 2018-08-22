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

			// Is it too slow to just look for collision with two pairs at the same time?
			// Works if one side is just spawning, above must be true
			if (m_colliders[0] != NULL && m_colliders[1] != NULL)
			{
				left_minion = m_colliders[0].component<Minion>();
				right_minion = m_colliders[1].component<Minion>();

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
				if ((m_colliders[0].component<Transform>()->position.x < m_colliders[1].component<Transform>()->position.x) &&
					(m_colliders[0].component<Render>()->name == "Player" && m_colliders[1].component<Render>()->name == "Player"))
				{
					haltMinion(m_colliders[0]);
				}
				else if ((m_colliders[0].component<Transform>()->position.x > m_colliders[1].component<Transform>()->position.x) &&
					(m_colliders[0].component<Render>()->name == "Enemy" && m_colliders[1].component<Render>()->name == "Enemy"))
				{
					haltMinion(m_colliders[0]);
				}
				else if ((m_colliders[0].component<Transform>()->position.x < m_colliders[1].component<Transform>()->position.x) &&
						(m_colliders[0].component<Render>()->name == "Player" && m_colliders[1].component<Render>()->name == "Enemy"))
				{
					attackMinion(m_colliders[0]);
				}
				else if ((m_colliders[0].component<Transform>()->position.x > m_colliders[1].component<Transform>()->position.x) &&
						(m_colliders[0].component<Render>()->name == "Enemy" && m_colliders[1].component<Render>()->name == "Player"))
				{
					attackMinion(m_colliders[0]);
				}
			}			
		}

		virtual void receive(const utils::Collision & collision) { m_colliders = { collision.left, collision.right }; }

	private:
		std::array<Entity, 2> m_colliders;
	};
}
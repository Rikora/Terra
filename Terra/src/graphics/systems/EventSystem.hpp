#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/Collision.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/Animation.hpp>
#include <graphics/components/PlayerMinion.hpp>
#include <array>

using namespace entityx;

namespace px
{
	class EventSystem : public System<EventSystem>, public Receiver<EventSystem>
	{
	public:
		virtual void configure(EventManager & event_manager) override { event_manager.subscribe<utils::Collision>(*this); }

		virtual void update(EntityManager & es, EventManager & events, TimeDelta dt) override
		{
			ComponentHandle<PlayerMinion> playerMinion, left_minion, right_minion;

			for (auto minion : es.entities_with_components(playerMinion))
				playerMinion->minion->attack(minion);

			// Only for player monk minions for now
			if (m_colliders[0] != NULL && m_colliders[1] != NULL)
			{
				for (auto left_entity : es.entities_with_components(left_minion))
				{
					for (auto right_entity : es.entities_with_components(right_minion))
					{
						if (left_entity == right_entity) continue;

						if (m_colliders[0].component<Transform>()->position.x < m_colliders[1].component<Transform>()->position.x)
						{
							if ((left_entity == m_colliders[0]) && (right_entity == m_colliders[1] && right_minion->minion->isAttacking()) ||
								(left_entity == m_colliders[0]) && (right_entity == m_colliders[1] && right_minion->minion->isFrontAttacking()))
							{
								// Halt the minion behind
								left_minion->minion->setVelocity(0.f);
								left_entity.component<Animation>()->animations->playAnimation("idle", true);
								left_minion->minion->setFrontAttacking(true);
							}
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
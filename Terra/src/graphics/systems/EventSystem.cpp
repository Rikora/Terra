////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/systems/EventSystem.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/Animation.hpp>
#include <graphics/components/PlayerMinion.hpp>

namespace px
{
	void EventSystem::configure(entityx::EventManager & event_manager)
	{
		event_manager.subscribe<utils::Collision>(*this);
	}

	void EventSystem::update(entityx::EntityManager & es, entityx::EventManager & events, TimeDelta dt)
	{
		ComponentHandle<PlayerMinion> playerMinion, left_minion, right_minion;

		for (auto minion : es.entities_with_components(playerMinion))
			playerMinion->minion->attack(minion);

		// Only for player monk minions for now
		if (m_colliders[0] != NULL && m_colliders[1] != NULL)
		{
			for (auto left_entity  : es.entities_with_components(left_minion))
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

	void EventSystem::receive(const utils::Collision & collision)
	{
		m_colliders = { collision.left, collision.right };
	}
}
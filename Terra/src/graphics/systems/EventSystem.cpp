////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/systems/EventSystem.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/PlayerMinion.hpp>

namespace px
{
	EventSystem::EventSystem(std::vector<std::unique_ptr<PlayerMinion>> & playerMinions) : m_playerMinions(playerMinions)
	{
	}

	void EventSystem::configure(entityx::EventManager & event_manager)
	{
		event_manager.subscribe<utils::Collision>(*this);
	}

	void EventSystem::update(entityx::EntityManager & entities, entityx::EventManager & events, TimeDelta dt)
	{
		// This is some ugly shit, will have to come up with a better solution? Lua script?
		if (m_colliders[0] != NULL && m_colliders[1] != NULL)
		{
			for (auto & minion_left : m_playerMinions)
			{
				for (auto & minion_right : m_playerMinions)
				{
					if (minion_left == minion_right) continue;

					if (m_colliders[0].component<Transform>()->position.x < m_colliders[1].component<Transform>()->position.x)
					{
						if (minion_left->getMinion() == m_colliders[0] && (minion_right->getMinion() == m_colliders[1] && minion_right->isAttacking()))
						{
							// Halt the minion behind
							minion_left->setVelocity(0.f);
							minion_left->playAnimation(Animations::Player_Monk_Idle_Right, true);
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
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
		// This is too deep so the update will halter, need a better solution!
		for (auto collider_left : m_colliders)
		{
			for (auto collider_right : m_colliders)
			{
				for (auto & minion_left : m_playerMinions)
				{
					for (auto & minion_right : m_playerMinions)
					{
						if (minion_left == minion_right) continue;

						if (collider_left.component<Transform>()->position.x < collider_right.component<Transform>()->position.x)
						{
							if ((minion_left->getMinion() == collider_left) && (minion_right->getMinion() == collider_right && minion_right->isAttacking()) ||
								(minion_left->getMinion() == collider_left) && (minion_right->getMinion() == collider_right && minion_right->isFrontAttacking()))
							{
								// Halt the minion behind
								minion_left->setVelocity(0.f);
								minion_left->playAnimation(Animations::Player_Monk_Idle_Right, true);
								minion_left->setFrontAttacking(true);
							}
						}
					}
				}
			}
		}

		m_colliders.clear();
	}

	void EventSystem::receive(const utils::Collision & collision)
	{
		m_colliders.push_back(collision.left);
		m_colliders.push_back(collision.right);
	}
}
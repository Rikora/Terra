#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/Collision.hpp>
#include <array>

namespace px
{
	class PlayerMinion;

	class EventSystem : public System<EventSystem>, public Receiver<EventSystem>
	{
	public:
		EventSystem(std::vector<std::unique_ptr<PlayerMinion>> & playerMinions);

		virtual void configure(entityx::EventManager & event_manager) override;
		virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, TimeDelta dt) override;
		virtual void receive(const utils::Collision & collision);

	private:
		std::vector<std::unique_ptr<PlayerMinion>> & m_playerMinions;
		std::array<Entity, 2> m_colliders;
	};
}
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/Collision.hpp>
#include <array>

namespace px
{
	class EventSystem : public System<EventSystem>, public Receiver<EventSystem>
	{
	public:
		virtual void configure(entityx::EventManager & event_manager) override;
		virtual void update(entityx::EntityManager & es, entityx::EventManager & events, TimeDelta dt) override;
		virtual void receive(const utils::Collision & collision);

	private:
		std::array<Entity, 2> m_colliders;
	};
}
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/Collision.hpp>

namespace px
{
	struct DebugSystem : public System<DebugSystem>, public Receiver<DebugSystem>
	{
		void configure(entityx::EventManager & event_manager) 
		{
			event_manager.subscribe<utils::Collision>(*this);
		}

		void update(entityx::EntityManager & entities, entityx::EventManager & events, TimeDelta dt) {}

		void receive(const utils::Collision & collision) 
		{
			std::cout << "entities collided: " << collision.left << " and " << collision.right << std::endl;
		}
	};
}
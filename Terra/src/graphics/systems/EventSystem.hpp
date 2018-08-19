#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/Collision.hpp>

namespace px
{
	class EventSystem : public System<EventSystem>, public Receiver<EventSystem>
	{
	public:
		virtual void configure(entityx::EventManager & event_manager) override
		{
			event_manager.subscribe<utils::Collision>(*this);
		}

		virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, TimeDelta dt) override 
		{

		}

		virtual void receive(const utils::Collision & collision)
		{	
			/*auto left = collision.left;
			auto right = collision.right;

			if (left.component<Transform>()->position.x < right.component<Transform>()->position.x)
				std::cout << "Yes\n";
			else
				std::cout << "No\n";*/
		}
	};
}
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>

using namespace entityx;

namespace px
{
	class CollisionSystem : public System<CollisionSystem>
	{
	public:
		virtual void update(EntityManager & es, EventManager & events, TimeDelta dt) override;
	};
}
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>

using namespace entityx;

namespace px
{
	class AnimationSystem : public System<AnimationSystem>
	{
	public:
		AnimationSystem();

	public:
		virtual void update(EntityManager &es, EventManager &events, TimeDelta dt) override;
	};
}
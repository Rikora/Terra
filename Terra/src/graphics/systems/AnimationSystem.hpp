#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>

using namespace entityx;

namespace sf
{
	class Clock;
}

namespace px
{
	class AnimationSystem : public System<AnimationSystem>
	{
	public:
		explicit AnimationSystem(sf::Clock & animationClock);

	public:
		virtual void update(EntityManager &es, EventManager &events, TimeDelta dt) override;

	private:
		sf::Clock & m_animationClock;
	};
}
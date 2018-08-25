#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/Entity.h>
#include <SFML/System/Vector2.hpp>

using namespace entityx;

namespace px
{
	struct Healthbar
	{
		explicit Healthbar(Entity background, Entity bar, const sf::Vector2f & backgroundOffset, const sf::Vector2f & barOffset,
						   const float & healthScaleX) : background(background), bar(bar), backgroundOffset(backgroundOffset), 
						   barOffset(barOffset), healthScaleX(healthScaleX) {}

		Entity background, bar;
		sf::Vector2f backgroundOffset, barOffset;
		float healthScaleX;
	};
}
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/Vector2.hpp>

namespace px
{
	// We are not interested in rotation and scale for now
	struct Transform
	{
		explicit Transform(const sf::Vector2f & position) : position(position) {}

		sf::Vector2f position;
	};
}
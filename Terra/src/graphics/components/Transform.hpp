#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/Vector2.hpp>

namespace px
{
	struct Transform
	{
		explicit Transform(const sf::Vector2f & position, const sf::Vector2f & scale) : position(position), scale(scale) {}

		sf::Vector2f position, scale;
	};
}
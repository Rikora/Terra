#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Rect.hpp>

namespace px
{
	struct BoundingBox
	{
		// The position of the bounding box is determined by the sprite
		BoundingBox(const sf::Vector2f & size, const sf::Vector2f offset) : boundingBox(0.f, 0.f, size.x, size.y), offset(offset) {}

		sf::FloatRect boundingBox;
		sf::Vector2f offset;
	};
}

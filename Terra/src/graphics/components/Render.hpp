#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <utils/Helper.hpp>
#include <string>

namespace px
{
	struct Render
	{
		explicit Render(std::unique_ptr<sf::Sprite> sprite, const std::string & name, const uint & layer) : sprite(std::move(sprite)), name(name), layer(layer) {}

		std::unique_ptr<sf::Sprite> sprite;
		std::string name;
		uint layer;
	};
}
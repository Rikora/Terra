#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace px
{
	struct Render
	{
		explicit Render(std::unique_ptr<sf::Sprite> sprite, const std::string & name) : sprite(std::move(sprite)), name(name) {}

		std::unique_ptr<sf::Sprite> sprite;
		std::string name;
	};
}
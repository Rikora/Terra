#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include <SFML/Graphics/Text.hpp>

namespace px
{
	struct Text
	{
		explicit Text(std::unique_ptr<sf::Text> text) : text(std::move(text)) {}

		std::unique_ptr<sf::Text> text;
	};
}

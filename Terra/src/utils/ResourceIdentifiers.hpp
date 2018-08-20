#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <Thor/Animations/Animator.hpp>

namespace Textures
{
	enum ID
	{
		Icon,
		Monk,
		Background,
		PlaceHolder,
	};
}

namespace Fonts
{
	enum ID
	{
		Main
	};
}

namespace px
{
	namespace utils
	{
		template <typename Resource, typename Identifier>
		class ResourceHolder;
	}
}

using TextureHolder = px::utils::ResourceHolder<sf::Texture, Textures::ID>;
using ImageHolder = px::utils::ResourceHolder<sf::Image, Textures::ID>;
using FontHolder = px::utils::ResourceHolder<sf::Font, Fonts::ID>;
using AnimationsHolder = thor::AnimationMap<sf::Sprite, std::string>;
using Animator = thor::Animator<sf::Sprite, std::string>;
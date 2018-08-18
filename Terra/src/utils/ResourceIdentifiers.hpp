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

namespace Animations
{
	enum ID
	{
		Player_Monk_Idle_Right,
		Player_Monk_Walk_Right,
		Player_Monk_Attack_Right
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
using AnimationsHolder = thor::AnimationMap<sf::Sprite, Animations::ID>;
using Animator = thor::Animator<sf::Sprite, Animations::ID>;
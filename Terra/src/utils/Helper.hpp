#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/Vector2.hpp>

using uint = unsigned int;

constexpr uint screen_width = 1000;
constexpr uint screen_height = 700;
#define PLAYER_BASE_POSITION sf::Vector2f(200.f, 620.f) //10.f -> x
#define ENEMY_BASE_POSITION sf::Vector2f(600.f, 620.f) //960.f -> x

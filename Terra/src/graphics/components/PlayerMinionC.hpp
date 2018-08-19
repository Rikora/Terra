#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/PlayerMinion.hpp>

using namespace entityx;

namespace px
{
	struct PlayerMinionC
	{
		PlayerMinionC(Entity & entity) : minion(std::make_unique<PlayerMinion>(entity)) {}

		std::unique_ptr<PlayerMinion> minion;
	};
}
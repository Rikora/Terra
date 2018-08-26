#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/Helper.hpp>

namespace px
{
	namespace utils
	{
		struct GameManager
		{
			uint playerGold = 1000;

			// Sample values
			inline uint convertResourceType(const std::string & type)
			{
				uint value;

				if (type == "Monk")
					value = 100;
				else if (type == "SpearOrc")
					value = 100;

				return value;
			}
		};
	}
}
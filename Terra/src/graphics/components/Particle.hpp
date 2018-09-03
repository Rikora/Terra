#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include <utils/ParticleLoader.hpp>

namespace px
{
	struct Particle
	{
		explicit Particle(std::unique_ptr<utils::ParticleLoader> particle) : particle(std::move(particle)) {}

		std::unique_ptr<utils::ParticleLoader> particle;
	};
}

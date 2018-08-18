#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <SFML/Graphics/Shape.hpp>
#include <utils/Helper.hpp>

using namespace entityx;

namespace sf
{
	class RenderTarget;
	class RectangleShape;
}

namespace px
{
	class RenderSystem : public System<RenderSystem>
	{
	public:
		explicit RenderSystem(sf::RenderTarget & target, std::vector<uint> & layers);

	public:
		virtual void update(EntityManager &es, EventManager &events, TimeDelta dt) override;

	private:
		sf::RectangleShape getBoundingRect(const sf::FloatRect & rect, const sf::Vector2f & offset);

	private:
		sf::RenderTarget & m_target;
		std::vector<uint> & m_layers;
	};
}
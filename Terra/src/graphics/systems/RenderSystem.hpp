#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <SFML/Graphics/Shape.hpp>
#include <graphics/components/Render.hpp>
#include <graphics/components/BoundingBox.hpp>
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
		explicit RenderSystem(sf::RenderTarget & target, std::vector<uint> & layers) : m_target(target), m_layers(layers) {}

	public:
		virtual void update(EntityManager &es, EventManager &events, TimeDelta dt) override
		{
			ComponentHandle<Render> render;

			for (auto layer : m_layers)
			{
				for (auto entity : es.entities_with_components(render))
				{
					if (render->layer == layer)
					{
						m_target.draw(*render->sprite.get());

						if (entity.has_component<BoundingBox>())
						{
							auto box = entity.component<BoundingBox>();
							m_target.draw(getBoundingRect(box->boundingBox, box->offset));
						}
					}
				}
			}
		}

	private:
		sf::RectangleShape getBoundingRect(const sf::FloatRect & rect, const sf::Vector2f & offset)
		{
			sf::RectangleShape shape;
			shape.setPosition(sf::Vector2f(rect.left + offset.x, rect.top + offset.y));
			shape.setSize(sf::Vector2f(rect.width, rect.height));
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineColor(sf::Color::Green);
			shape.setOutlineThickness(1.f);
			return shape;
		}

	private:
		sf::RenderTarget & m_target;
		std::vector<uint> & m_layers;
	};
}
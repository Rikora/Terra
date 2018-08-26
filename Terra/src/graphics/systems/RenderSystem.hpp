#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <SFML/Graphics/Shape.hpp>
#include <graphics/components/Render.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/BoundingBox.hpp>
#include <graphics/components/Text.hpp>
#include <graphics/components/Minion.hpp>
#include <utils/Helper.hpp>

using namespace entityx;

namespace sf
{
	class RenderTarget;
	class RectangleShape;
	class CircleShape;
}

namespace px
{
	class RenderSystem : public System<RenderSystem>
	{
	public:
		explicit RenderSystem(sf::RenderTarget & target, std::vector<uint> & layers, bool & drawDebugData) : m_target(target), m_layers(layers),
						      m_drawDebugData(drawDebugData) {}

	public:
		inline virtual void update(EntityManager &es, EventManager &events, TimeDelta dt) override
		{
			ComponentHandle<Render> render;
			ComponentHandle<Text> text;

			for (auto layer : m_layers)
			{
				for (auto entity : es.entities_with_components(render))
				{
					if (render->layer == layer)
					{
						m_target.draw(*render->sprite.get());

						if (m_drawDebugData)
						{
							if (entity.has_component<BoundingBox>())
							{
								auto box = entity.component<BoundingBox>();
								m_target.draw(drawRect(box->boundingBox));
							}

							if (entity.has_component<Minion>())
							{
								auto minion = entity.component<Minion>();
								m_target.draw(drawCircle(minion->minion->getFrontCollider()));
							}
						}
					}
				}
			}

			for (auto entity : es.entities_with_components(text))
				m_target.draw(*text->text.get());
		}

	private:
		inline sf::RectangleShape drawRect(const sf::FloatRect & rect)
		{
			sf::RectangleShape shape;
			shape.setPosition(sf::Vector2f(rect.left, rect.top));
			shape.setSize(sf::Vector2f(rect.width, rect.height));
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineColor(sf::Color::Green);
			shape.setOutlineThickness(1.f);
			return shape;
		}

		inline sf::CircleShape drawCircle(const sf::Vector2f & position)
		{
			sf::CircleShape shape;
			shape.setPosition(position);
			shape.setRadius(3.f);
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineColor(sf::Color::Magenta);
			shape.setOutlineThickness(1.f);
			return shape;
		}

	private:
		sf::RenderTarget & m_target;
		std::vector<uint> & m_layers;
		bool & m_drawDebugData;
	};
}
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/systems/RenderSystem.hpp>
#include <graphics/components/Render.hpp>
#include <graphics/components/BoundingBox.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace px
{
	RenderSystem::RenderSystem(sf::RenderTarget & target, std::vector<uint> & layers) : m_target(target), m_layers(layers)
	{
	}

	void RenderSystem::update(EntityManager & es, EventManager & events, TimeDelta dt)
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
						box->boundingBox.left = render->sprite->getPosition().x;
						box->boundingBox.top = render->sprite->getPosition().y;
						m_target.draw(getBoundingRect(box->boundingBox, box->offset)); // Position system will be a better solution?
					}	
				}
			}
		}
	}

	sf::RectangleShape RenderSystem::getBoundingRect(const sf::FloatRect & rect, const sf::Vector2f & offset)
	{
		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(rect.left + offset.x, rect.top + offset.y));
		shape.setSize(sf::Vector2f(rect.width, rect.height));
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Green);
		shape.setOutlineThickness(1.f);
		return shape;
	}
}
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/systems/RenderSystem.hpp>
#include <graphics/components/Render.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace px
{
	RenderSystem::RenderSystem(sf::RenderTarget & target) : m_target(target)
	{
	}

	void RenderSystem::update(EntityManager & es, EventManager & events, TimeDelta dt)
	{
		ComponentHandle<Render> render;

		for (auto entity : es.entities_with_components(render))
		{
			m_target.draw(*render->sprite.get());
			//m_target.draw(getBoundingRect(render->sprite->getGlobalBounds())); // Draw bounding rect of the shape
		}
	}

	sf::RectangleShape RenderSystem::getBoundingRect(const sf::FloatRect & rect)
	{
		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(rect.left, rect.top));
		shape.setSize(sf::Vector2f(rect.width, rect.height));
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Green);
		shape.setOutlineThickness(1.f);
		return shape;
	}
}
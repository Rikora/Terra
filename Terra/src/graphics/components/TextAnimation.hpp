#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/Entity.h>
#include <graphics/components/Text.hpp>
#include <graphics/components/Transform.hpp>

using namespace entityx;

// Class only intended for text fading animations moving upwards
namespace px
{
	class AnimatedText
	{
	public:
		explicit AnimatedText(const float & velocity, const sf::Uint8 & alphaStep) : m_velocity(velocity), m_alphaStep(alphaStep) {}
		~AnimatedText() = default;

	public:
		inline void update(Entity & entity, double dt)
		{
			auto text = entity.component<Text>();
			text->text->setFillColor(text->text->getFillColor() - sf::Color(0, 0, 0, m_alphaStep));
			entity.component<Transform>()->position.y -= m_velocity * (float)dt;

			if ((int)text->text->getFillColor().a <= 0)
				entity.destroy();
		}

	private:
		float m_velocity;
		sf::Uint8 m_alphaStep;
	};

	struct TextAnimation
	{
		explicit TextAnimation(const float & velocity, const sf::Uint8 & alphaStep) : text(std::make_unique<AnimatedText>(velocity, alphaStep)) {}

		std::unique_ptr<AnimatedText> text;
	};
}
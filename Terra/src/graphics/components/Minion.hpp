#pragma once
#include <entityx/Entity.h>
#include <graphics/components/Transform.hpp>
#include <graphics/components/Animation.hpp>

using namespace entityx;

namespace px
{
	class MinionScript
	{
	public:
		MinionScript(const float & velocity, const sf::Vector2f & offset) : m_isAttacking(false), m_isFrontAttacking(false), 
					 m_velocity(velocity), m_offset(offset) {};
		~MinionScript() = default;

	public:
		void attack(Entity & minion)
		{
			// This should be replaced with enemy/player collision notifier code
			if (minion.component<Transform>()->position.x < 300.f)
				minion.component<Transform>()->position += sf::Vector2f(m_velocity, 0.f) * (1.f / 60.f);
			else
			{
				if (!m_isAttacking)
				{
					minion.component<Animation>()->animations->playAnimation("attack", true);
					m_isAttacking = true;
					m_velocity = 0.f;
				}
			}
		}

	public:
		void setVelocity(const float & velocity) { m_velocity = velocity;  }
		void setFrontAttacking(const bool & frontAttacking) { m_isFrontAttacking = frontAttacking; }
		void setFrontCollider(const sf::Vector2f & pos) { m_frontCollider = pos + m_offset; }

	public:
		bool isAttacking() const { return m_isAttacking; }
		bool isFrontAttacking() const { return m_isFrontAttacking; }
		sf::Vector2f getFrontCollider() const { return m_frontCollider; }

	private:
		float m_velocity;
		bool m_isAttacking;
		bool m_isFrontAttacking;
		sf::Vector2f m_frontCollider;
		sf::Vector2f m_offset;
	};

	struct Minion
	{
		Minion(const float & velocity, const sf::Vector2f & offset) : minion(std::make_unique<MinionScript>(velocity, offset)) {}

		std::unique_ptr<MinionScript> minion;
	};
}
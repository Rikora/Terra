#pragma once
#include <entityx/Entity.h>
#include <graphics/components/Render.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/Animation.hpp>

using namespace entityx;

namespace px
{
	class MinionScript
	{
	public:
		MinionScript(const float & velocity, const sf::Vector2f & offset, const uint & health) : m_isAttacking(false), m_isFrontAttacking(false), 
					 m_velocity(velocity), m_offset(offset), m_health(health) {};
		~MinionScript() = default;

	public:
		void attack(Entity & minion, double dt)
		{
			minion.component<Transform>()->position += sf::Vector2f(m_velocity, 0.f) * (float)dt;
		}

	public:
		void setVelocity(const float & velocity) { m_velocity = velocity;  }
		void setAttacking(const bool & attacking) { m_isAttacking = attacking; }
		void setFrontAttacking(const bool & frontAttacking) { m_isFrontAttacking = frontAttacking; }
		void setFrontCollider(const sf::Vector2f & pos) { m_frontCollider = pos + m_offset; }
		void setHealth(const uint & health) { m_health = health; }

	public:
		bool isAttacking() const { return m_isAttacking; }
		bool isFrontAttacking() const { return m_isFrontAttacking; }
		sf::Vector2f getFrontCollider() const { return m_frontCollider; }
		uint getHealth() const { return m_health; }

	private:
		uint m_health;
		float m_velocity;
		bool m_isAttacking;
		bool m_isFrontAttacking;
		sf::Vector2f m_frontCollider;
		sf::Vector2f m_offset;
	};

	struct Minion
	{
		Minion(const float & velocity, const sf::Vector2f & offset, const uint & health) : 
				minion(std::make_unique<MinionScript>(velocity, offset, health)) {}

		std::unique_ptr<MinionScript> minion;
	};
}
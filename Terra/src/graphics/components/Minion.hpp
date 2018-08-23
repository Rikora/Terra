#pragma once
#include <entityx/Entity.h>
#include <Thor/Time/StopWatch.hpp>
#include <graphics/components/Render.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/Animation.hpp>

using namespace entityx;

namespace px
{
	class MinionScript
	{
	public:
		MinionScript(const float & velocity, const sf::Vector2f & offset, const uint & damage, const uint & health) : m_isAttacking(false), m_isFrontAttacking(false), 
					 m_velocity(velocity), m_tmpVelocity(velocity), m_offset(offset), m_damage(damage), m_health(health) {};
		~MinionScript() = default;

	public:
		void resetVelocity() { m_velocity = m_tmpVelocity; }
		void update(Entity & minion, double dt)
		{	
			minion.component<Transform>()->position += sf::Vector2f(m_velocity, 0.f) * (float)dt;

			if (m_target == NULL)
				resetVelocity();

			if (m_health <= 0)
				minion.destroy();
		}

	public:
		void setVelocity(const float & velocity) { m_velocity = velocity;  }
		void setAttacking(const bool & attacking) { m_isAttacking = attacking; }
		void setFrontAttacking(const bool & frontAttacking) { m_isFrontAttacking = frontAttacking; }
		void setFrontCollider(const sf::Vector2f & pos) { m_frontCollider = pos + m_offset; }
		void setHealth(const uint & health) { m_health = health; }
		void setTarget(Entity & target) { m_target = target; }

	public:
		bool isAttacking() const { return m_isAttacking; }
		bool isFrontAttacking() const { return m_isFrontAttacking; }
		sf::Vector2f getFrontCollider() const { return m_frontCollider; }
		uint getDamage() const { return m_damage; }
		uint getHealth() const { return m_health; }
		Entity getTarget() { return m_target; }

	public:
		thor::StopWatch m_damageWatch;

	private:
		uint m_damage;
		uint m_health;
		float m_velocity;
		float m_tmpVelocity;
		bool m_isAttacking;
		bool m_isFrontAttacking;
		sf::Vector2f m_frontCollider;
		sf::Vector2f m_offset;
		Entity m_target;
	};

	struct Minion
	{
		Minion(const float & velocity, const sf::Vector2f & offset, const uint & damage, const uint & health) : 
				minion(std::make_unique<MinionScript>(velocity, offset, damage, health)) {}

		std::unique_ptr<MinionScript> minion;
	};
}
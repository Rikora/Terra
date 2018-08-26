#pragma once
#include <entityx/Entity.h>
#include <Thor/Time/StopWatch.hpp>

using namespace entityx;

namespace px
{
	class MinionScript
	{
	public:
		explicit MinionScript(const float & velocity, const sf::Vector2f & offset, const uint & damage, const uint & health) : m_isAttacking(false), m_isFrontAttacking(false), 
					 m_velocity(velocity), m_tmpVelocity(velocity), m_offset(offset), m_damage(damage), m_health(health), m_maxHealth(health) {};
		~MinionScript() = default;

	public:
		void resetVelocity() { m_velocity = m_tmpVelocity; }

	public:
		void setVelocity(const float & velocity) { m_velocity = velocity;  }
		void setAttacking(const bool & attacking) { m_isAttacking = attacking; }
		void setFrontAttacking(const bool & frontAttacking) { m_isFrontAttacking = frontAttacking; }
		void setFrontCollider(const sf::Vector2f & pos) { m_frontCollider = pos + m_offset; }
		void setHealth(const uint & health) { m_health = health; }
		void setTarget(Entity & target) { m_target = target; }

	public:
		float getVelocity() const { return m_velocity; }
		bool isAttacking() const { return m_isAttacking; }
		bool isFrontAttacking() const { return m_isFrontAttacking; }
		sf::Vector2f getFrontCollider() const { return m_frontCollider; }
		uint getDamage() const { return m_damage; }
		uint getHealth() const { return m_health; }
		uint getMaxHealth() const { return m_maxHealth; }
		Entity getTarget() { return m_target; }

	public:
		thor::StopWatch m_damageWatch;

	private:
		uint m_damage;
		uint m_health;
		uint m_maxHealth;
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
		explicit Minion(const float & velocity, const sf::Vector2f & offset, const uint & damage, const uint & health) : 
				minion(std::make_unique<MinionScript>(velocity, offset, damage, health)) {}

		std::unique_ptr<MinionScript> minion;
	};
}
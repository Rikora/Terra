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
		MinionScript() : m_isAttacking(false), m_isFrontAttacking(false), m_velocity(60.f) {};
		~MinionScript() = default;

	public:
		void attack(Entity & minion)
		{
			if (minion.component<Transform>()->position.x < 300.f)
				minion.component<Transform>()->position += sf::Vector2f(m_velocity, 0.f) * (1.f / 60.f);
			else
			{
				if (!m_isAttacking)
				{
					minion.component<Animation>()->animations->playAnimation("attack", true);
					m_isAttacking = true;
					//m_velocity = 0.f;
				}
			}
		}

	public:
		void setVelocity(const float & velocity) { m_velocity = velocity;  }
		void setFrontAttacking(const bool & frontAttacking) { m_isFrontAttacking = frontAttacking; }

	public:
		bool isAttacking() const { return m_isAttacking; }
		bool isFrontAttacking() const { return m_isFrontAttacking; }

	private:
		float m_velocity;
		bool m_isAttacking;
		bool m_isFrontAttacking;
	};

	struct PlayerMinion
	{
		PlayerMinion() : minion(std::make_unique<MinionScript>()) {}

		std::unique_ptr<MinionScript> minion;
	};
}
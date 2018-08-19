////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/PlayerMinion.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/Animation.hpp>

namespace px
{
	PlayerMinion::PlayerMinion(Entity & entity) : m_minion(entity), m_isAttacking(false), m_isFrontAttacking(false), m_velocity(60.f)
	{
	}

	void PlayerMinion::attack()
	{
		if (m_minion.component<Transform>()->position.x < 300.f) 
			m_minion.component<Transform>()->position += sf::Vector2f(m_velocity, 0.f) * (1.f / 60.f);
		else
		{
			if (!m_isAttacking)
			{
				m_minion.component<Animation>()->animations->playAnimation(Animations::Player_Monk_Attack_Right, true);
				m_isAttacking = true;
				//m_velocity = 0.f;
			}
		}
	}

	void PlayerMinion::setVelocity(const float & velocity)
	{
		m_velocity = velocity;
	}

	void PlayerMinion::setFrontAttacking(const bool & frontAttacking)
	{
		m_isFrontAttacking = frontAttacking;
	}

	bool PlayerMinion::isAttacking() const
	{
		return m_isAttacking;
	}

	bool PlayerMinion::isFrontAttacking() const
	{
		return m_isFrontAttacking;
	}
}
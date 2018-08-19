////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/PlayerMinion.hpp>
#include <graphics/Scene.hpp>
#include <utils/Utility.hpp>

namespace px
{
	PlayerMinion::PlayerMinion(Scene & scene) : m_scene(scene), m_isAttacking(false), m_velocity(60.f)
	{
		m_minion = m_scene.createEntity("Monk", Textures::Monk, PLAYER_BASE_POSITION, 1);
		m_minion.assign<Animation>();
		m_minion.assign<BoundingBox>(sf::Vector2f(32.f, 54.f), sf::Vector2f(15.f, 10.f));
	}

	void PlayerMinion::attack()
	{
		if (m_minion.component<Transform>()->position.x < 200.f) 
			m_minion.component<Transform>()->position += sf::Vector2f(m_velocity, 0.f) * (1.f / 60.f);
		else
		{
			if (!m_isAttacking)
			{
				playAnimation(Animations::Player_Monk_Attack_Right, true);
				m_isAttacking = true;
			}
		}
	}

	void PlayerMinion::setVelocity(const float & velocity)
	{
		m_velocity = velocity;
	}

	void PlayerMinion::addAnimation(Animations::ID id, int row, int frames, sf::Time duration)
	{
		thor::FrameAnimation frameAnim;
		m_minion.component<Animation>()->animations.addAnimation(id, utils::addFrames(frameAnim, row, frames), duration);
	}

	void PlayerMinion::playAnimation(Animations::ID id, bool repeat)
	{
		repeat ? m_minion.component<Animation>()->animator.play() << id << thor::Playback::loop(id) : m_minion.component<Animation>()->animator.play();
	}

	Entity PlayerMinion::getMinion() const
	{
		return m_minion;
	}

	bool PlayerMinion::isAttacking() const
	{
		return m_isAttacking;
	}
}
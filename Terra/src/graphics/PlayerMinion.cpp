////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/PlayerMinion.hpp>
#include <graphics/Scene.hpp>
#include <utils/Utility.hpp>

namespace px
{
	// TODO: make this class more user friendly for other type of player/enemy minions -> addAnimation()...
	PlayerMinion::PlayerMinion(Scene & scene) : m_scene(scene), m_attacking(false)
	{
		m_minion = m_scene.createEntity("Monk", Textures::Monk, PLAYER_BASE_POSITION, 1);
		m_minion.assign<Animation>();
		addAnimations();
	}

	void PlayerMinion::attack()
	{
		if (m_minion.component<Render>()->sprite->getPosition().x < 100.f) // 100.f is a test for now
			m_minion.component<Render>()->sprite->move(sf::Vector2f(60.f, 0.f) * (1.f / 60.f));
		else
		{
			if (!m_attacking)
			{
				m_minion.component<Animation>()->animator.stop();
				m_minion.component<Animation>()->animator.play() << Animations::Player_Monk_Attack_Right << thor::Playback::loop(Animations::Player_Monk_Attack_Right);
				m_attacking = true;
			}
		}
	}

	void PlayerMinion::addAnimations()
	{
		m_minion.component<Animation>()->frameAnimations.resize(2);
		m_minion.component<Animation>()->animations.addAnimation(Animations::Player_Monk_Walk_Right,
			utils::addFrames(m_minion.component<Animation>()->frameAnimations[0], 11, 9), sf::seconds(1.f));
		m_minion.component<Animation>()->animations.addAnimation(Animations::Player_Monk_Attack_Right,
			utils::addFrames(m_minion.component<Animation>()->frameAnimations[1], 15, 6), sf::seconds(0.8f));

		// Play the walking animation from the start
		m_minion.component<Animation>()->animator.play() << Animations::Player_Monk_Walk_Right << thor::Playback::loop(Animations::Player_Monk_Walk_Right);
	}
}
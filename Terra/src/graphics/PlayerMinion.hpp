#pragma once
#include <entityx/Entity.h>
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>

using namespace entityx;

// Allow inheritance from Minion class in the future if needed?
namespace px
{
	class Scene;

	class PlayerMinion
	{
	public:
		explicit PlayerMinion(Scene & scene);
		~PlayerMinion() = default;
		
	public:
		void addAnimation(Animations::ID id, int row, int frames, sf::Time duration = sf::seconds(1.f));
		void playAnimation(Animations::ID id, bool repeat = false);
		void attack();

	public:
		void setVelocity(const float & velocity);
		void setFrontAttacking(const bool & frontAttacking);

	public:
		Entity getMinion() const;
		bool isAttacking() const;
		bool isFrontAttacking() const;

	private:
		Scene & m_scene;
		Entity m_minion;
		bool m_isAttacking;
		bool m_isFrontAttacking;
		float m_velocity;
	};
}
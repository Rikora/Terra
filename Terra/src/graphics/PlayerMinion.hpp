#pragma once
#include <entityx/Entity.h>

using namespace entityx;

namespace px
{
	// This could also be a lua script in the future?
	class PlayerMinion
	{
	public:
		PlayerMinion(Entity & entity);
		~PlayerMinion() = default;	
		void attack();

	public:
		void setVelocity(const float & velocity);
		void setFrontAttacking(const bool & frontAttacking);

	public:
		bool isAttacking() const;
		bool isFrontAttacking() const;

	private:
		Entity m_minion; // Used for caching
		float m_velocity;
		bool m_isAttacking;
		bool m_isFrontAttacking;
	};
}
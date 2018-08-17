#pragma once
#include <entityx/Entity.h>

using namespace entityx;

namespace px
{
	class Scene;

	class PlayerMinion
	{
	public:
		explicit PlayerMinion(Scene & scene);
		~PlayerMinion() = default;
		
	public:
		void attack();

	private:
		void addAnimations();

	private:
		Scene & m_scene;
		Entity m_minion;
		bool m_attacking;
	};
}
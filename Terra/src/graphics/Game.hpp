#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>
#include <utils/GameManager.hpp>
#include <entityx/Entity.h>
#include <memory>

using namespace entityx;

namespace px
{
	class Scene;

	class Game
	{
	public:
		Game();
		~Game();
		void run();

	private:
		void initScene();
		void pollEvents();
		void update(double dt);
		void render();
		void loadResources();

	private:
		sf::RenderWindow m_window;
		TextureHolder m_textures;
		ImageHolder m_images;
		FontHolder m_fonts;
		Entity m_goldText;
		utils::GameManager m_gameManager;

	private:
		std::unique_ptr<Scene> m_scene;
	};
}
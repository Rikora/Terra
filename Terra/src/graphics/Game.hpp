#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>
#include <memory>

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
		//FontHolder m_fonts;

	private:
		std::unique_ptr<Scene> m_scene;
	};
}
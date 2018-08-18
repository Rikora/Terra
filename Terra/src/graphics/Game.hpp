#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/RenderWindow.hpp>
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>
#include <Thor/Animations/FrameAnimation.hpp>
#include <memory>

namespace px
{
	class Scene;
	class PlayerMinion;

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
		std::unique_ptr<PlayerMinion> m_minion;
		std::vector<std::unique_ptr<PlayerMinion>> m_playerMinions;
	};
}
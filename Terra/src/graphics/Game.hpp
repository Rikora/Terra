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

	class Game
	{
	public:
		explicit Game();
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
		sf::Clock m_animationsClock;

	private:
		std::unique_ptr<Scene> m_scene;
	};
}
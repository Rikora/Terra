#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/RenderWindow.hpp>
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>
#include <Thor/Animations/FrameAnimation.hpp>
#include <memory>

namespace sf
{
	class Time;
}

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
		void update(sf::Time dt);
		void render();
		void loadResources();

	private:
		sf::RenderWindow m_window;
		TextureHolder m_textures;
		ImageHolder m_images;
		AnimationsHolder m_animations;
		Animator m_animator;
		//FontHolder m_fonts;
		thor::FrameAnimation m_walkRight;
		thor::FrameAnimation m_attackRight;
		Animations::ID m_currentAnimation;

	private:
		std::unique_ptr<Scene> m_scene;
	};
}
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/Game.hpp>
#include <graphics/Scene.hpp>
#include <graphics/PlayerMinion.hpp>
#include <utils/Helper.hpp>
#include <utils/Utility.hpp>
#include <SFML/Window/Event.hpp>

namespace px
{
	double timestep = 1.0 / 60.0;
	float stopPosition = 100.f;
	bool stopped = false;

	Game::Game() : m_window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Terra", sf::Style::Close,
							sf::ContextSettings(0U, 0U, 8U))
	{
		m_window.setVerticalSyncEnabled(true);
		loadResources();
		sf::Image icon = m_images.GetResource(Textures::Icon);
		m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		initScene();
	}

	Game::~Game()
	{
		m_scene->destroyEntities();
	}

	void Game::loadResources()
	{
		// Textures
		m_images.LoadResource(Textures::Icon, "src/res/icon/dragon.png");
		m_textures.LoadResource(Textures::Monk, "src/res/sprites/playerMonk.png");
		m_textures.LoadResource(Textures::Background, "src/res/sprites/wizardtower.png");
	}

	void Game::initScene()
	{
		m_scene = std::make_unique<Scene>(m_window, m_textures);
		m_minion = std::make_unique<PlayerMinion>(*m_scene.get());
		m_minion->addAnimation(Animations::Player_Monk_Idle_Right, 11, 1);
		m_minion->addAnimation(Animations::Player_Monk_Walk_Right, 11, 9);
		m_minion->addAnimation(Animations::Player_Monk_Attack_Right, 15, 6, sf::seconds(0.8f));
		m_minion->playAnimation(Animations::Player_Monk_Walk_Right, true);

		m_scene->createEntity("Background", Textures::Background, sf::Vector2f(0.f, 0.f), 0);
	}

	void Game::pollEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				m_window.close();
			/*if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
			{	
				auto minion = std::make_unique<PlayerMinion>(*m_scene.get());
				minion->addAnimation(Animations::Player_Monk_Idle_Right, 11, 1);
				minion->addAnimation(Animations::Player_Monk_Walk_Right, 11, 9);
				minion->addAnimation(Animations::Player_Monk_Attack_Right, 15, 6, sf::seconds(0.8f));
				minion->playAnimation(Animations::Player_Monk_Walk_Right, true);
				m_playerMinions.push_back(std::move(minion));
			}*/
		}
	}

	void Game::update(double dt)
	{
		/*for (auto & minion : m_playerMinions)
			minion->attack();*/

		m_minion->attack();
		m_scene->updateAnimationSystem(timestep);
	}

	void Game::render()
	{
		m_window.clear();
		m_scene->updateRenderSystem(timestep);
		m_window.display();
	}

	void Game::run()
	{
		while (m_window.isOpen())
		{
			pollEvents();
			update(timestep);
			render();
		}
	}
}
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/Game.hpp>
#include <graphics/Scene.hpp>
#include <SFML/Window/Event.hpp>

namespace px
{
	const double timestep = 1.0 / 60.0;

	Game::Game() : m_window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Terra", sf::Style::Close,
							sf::ContextSettings(0U, 0U, 8U)), m_drawDebugData(false)
	{
		m_window.setVerticalSyncEnabled(true);
		loadResources();
		sf::Image icon = m_images.getResource(Textures::Icon);
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
		m_images.loadResource(Textures::Icon, "src/res/icon/dragon.png");
		m_textures.loadResource(Textures::Background, "src/res/sprites/wizardtower.png");
		m_textures.loadResource(Textures::Healthbar, "src/res/sprites/healthbar.png");
		m_textures.loadResource(Textures::HealthbarBackground, "src/res/sprites/healthback.png");
		m_textures.loadResource(Textures::Monk, "src/res/sprites/playerMonk.png");
		m_textures.loadResource(Textures::SpearOrc, "src/res/sprites/spearOrc.png");

		// Fonts
		m_fonts.loadResource(Fonts::Game, "src/res/fonts/coolstory_regular.ttf");
	}

	void Game::initScene()
	{
		m_scene = std::make_unique<Scene>(m_window, m_textures, m_fonts, m_gameManager, m_drawDebugData);
		m_scene->createEntity("Background", Textures::Background, sf::Vector2f(0.f, 0.f));
		m_goldText = m_scene->createText("Gold: " + std::to_string(m_gameManager.playerGold), Fonts::Game, 22, sf::Vector2f(30.f, 35.f), sf::Color::Yellow);
		m_goldText.component<Text>()->text->setOutlineThickness(2.f);

		// Test code
		//m_scene->createMinion("Player", Textures::Monk);
	}

	void Game::pollEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				m_window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U)
				m_drawDebugData = !m_drawDebugData;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
			{
				m_scene->createMinion("Player", Textures::Monk);
				m_scene->createMinion("Enemy", Textures::SpearOrc);
			}
		}
	}

	void Game::update(double dt)
	{
		m_goldText.component<Text>()->text->setString("Gold: " + std::to_string(m_gameManager.playerGold));
		m_scene->updateTransformSystems(dt);
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
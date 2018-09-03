////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/Scene.hpp>
#include <graphics/systems/RenderSystem.hpp>
#include <graphics/systems/AnimationSystem.hpp>
#include <graphics/systems/TransformSystem.hpp>
#include <graphics/systems/CollisionSystem.hpp>
#include <utils/GameManager.hpp>

namespace px
{
	Scene::Scene(sf::RenderTarget & target, TextureHolder & textures, FontHolder & fonts, utils::GameManager & gameManager, bool & drawDebugData) : m_entities(m_events),
				 m_systems(m_entities, m_events), m_textures(textures), m_fonts(fonts), m_gameManager(gameManager)
	{
		m_layers = { 0, 1, 2 };
		initSystems(target, drawDebugData);
	}

	Entity Scene::createEntity(const std::string & name, Textures::ID texID, const sf::Vector2f & position, 
							   const sf::Vector2f & scale, const uint & layer)
	{
		auto entity = m_entities.create();
		auto sprite = std::make_unique<sf::Sprite>(m_textures.getResource(texID));
		sprite->setScale(scale);
		sprite->setPosition(position);
		entity.assign<Transform>(position, scale);
		entity.assign<Render>(std::move(sprite), name, layer);
		return entity;
	}

	Entity Scene::createText(const std::string & name, Fonts::ID fontID, const uint & fontSize, const sf::Vector2f & position, const sf::Color & color)
	{
		auto entity = m_entities.create();
		auto text = std::make_unique<sf::Text>(name, m_fonts.getResource(fontID), fontSize);
		text->setFillColor(color);
		text->setPosition(position);
		entity.assign<Transform>(position, sf::Vector2f(1.f, 1.f));
		entity.assign<Text>(std::move(text));
		return entity;
	}

	Entity Scene::createParticleSystem(const std::string & filePath, const sf::Vector2f & position)
	{
		auto entity = m_entities.create();
		auto system = std::make_unique<utils::ParticleLoader>(filePath, position);
		entity.assign<Particle>(std::move(system));
		return entity;
	}

	void Scene::createMinion(const std::string & name, const std::string & type, Textures::ID texID)
	{
		// Use a json file to store minion properties instead?
		if (name == "Player")
		{
			auto entity = createEntity(name, texID, PLAYER_BASE_POSITION, sf::Vector2f(1.f, 1.f), 1);
			entity.assign<Animation>();
			entity.assign<BoundingBox>(sf::Vector2f(30.f, 52.f), sf::Vector2f(15.f, 11.f));
			entity.assign<Minion>(type, 60.f, sf::Vector2f(56.f, 40.f), 10, 100);
			addHealthbars(entity, PLAYER_BASE_POSITION);

			auto anim = entity.component<Animation>();

			if (texID == Textures::Monk)
			{
				anim->animations->addAnimation("idle", 11, 1);
				anim->animations->addAnimation("walk", 11, 9);
				anim->animations->addAnimation("attack", 15, 6, sf::seconds(0.8f));
				anim->animations->playAnimation("walk", true);
				m_gameManager.playerGold -= m_gameManager.convertResourceType(type);
			}
		}
		else if (name == "Enemy")
		{
			auto entity = createEntity(name, texID, ENEMY_BASE_POSITION, sf::Vector2f(1.f, 1.f), 1);
			entity.assign<Animation>();
			entity.assign<BoundingBox>(sf::Vector2f(30.f, 52.f), sf::Vector2f(17.f, 11.f));
			entity.assign<Minion>(type, -60.f, sf::Vector2f(0.f, 40.f), 10, 100);
			addHealthbars(entity, ENEMY_BASE_POSITION);
			auto anim = entity.component<Animation>();

			if (texID == Textures::SpearOrc)
			{
				anim->animations->addAnimation("idle", 9, 1);
				anim->animations->addAnimation("walk", 9, 9);
				anim->animations->addAnimation("attack", 5, 8, sf::seconds(0.8f));
				anim->animations->playAnimation("walk", true);
			}
		}
	}

	void Scene::destroyEntities()
	{
		ComponentHandle<Render> render;

		for (auto entity : m_entities.entities_with_components(render))
			entity.destroy();
	}

	void Scene::updateRenderSystem(TimeDelta dt)
	{
		m_systems.update<RenderSystem>(dt);
	}

	void Scene::updateTransformSystems(TimeDelta dt)
	{
		m_systems.update<TransformSystem>(dt);
		m_systems.update<AnimationSystem>(dt);
		m_systems.update<CollisionSystem>(dt);
	}

	Entity Scene::getEntity(const std::string & name)
	{
		ComponentHandle<Render> render;
		Entity found;

		for (Entity entity : m_entities.entities_with_components(render))
			if (render->name == name)
				found = entity;

		return found;
	}

	void Scene::initSystems(sf::RenderTarget & target, bool & drawDebugData)
	{
		m_systems.add<RenderSystem>(target, m_layers, drawDebugData);
		m_systems.add<TransformSystem>();
		m_systems.add<AnimationSystem>();
		m_systems.add<CollisionSystem>(*this, m_gameManager);
		m_systems.configure();
	}

	void Scene::addHealthbars(Entity & entity, const sf::Vector2f & position)
	{
		entity.assign<Healthbar>(createEntity("Background", Textures::HealthbarBackground, position + sf::Vector2f(16.f, -3.f),
								 sf::Vector2f(0.15f, 0.25f), 1),
								 createEntity("Healthbar", Textures::Healthbar, position + sf::Vector2f(17.f, -1.f),
								 sf::Vector2f(0.14f, 0.15f), 2),
								 sf::Vector2f(16.f, -3.f), sf::Vector2f(17.f, -1.f), 0.14f);
	}
}
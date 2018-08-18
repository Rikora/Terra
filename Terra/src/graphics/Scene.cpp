////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <graphics/Scene.hpp>
#include <graphics/systems/RenderSystem.hpp>
#include <graphics/systems/AnimationSystem.hpp>
#include <graphics/systems/TransformSystem.hpp>

namespace px
{
	Scene::Scene(sf::RenderTarget & target, TextureHolder & textures) : m_entities(m_events), m_systems(m_entities, m_events),
																		m_textures(textures)
	{
		m_layers = { 0, 1 };
		initSystems(target);
	}

	Entity Scene::createEntity(const std::string & name, Textures::ID texID, const sf::Vector2f & position, const uint & layer)
	{
		auto entity = m_entities.create();
		auto sprite = std::make_unique<sf::Sprite>(m_textures.GetResource(texID));
		sprite->setPosition(position);
		entity.assign<Transform>(position);
		entity.assign<Render>(std::move(sprite), name, layer);
		return entity;
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
	}

	EntityManager & Scene::getEntities()
	{
		return m_entities;
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

	void Scene::initSystems(sf::RenderTarget & target)
	{
		m_systems.add<RenderSystem>(target, m_layers);
		m_systems.add<TransformSystem>();
		m_systems.add<AnimationSystem>();
		m_systems.configure();
	}
}
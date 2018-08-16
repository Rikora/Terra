#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <graphics/components/Render.hpp>
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>

using namespace entityx;

namespace sf
{
	class RenderTarget;
}

namespace px
{
	class Scene : public EntityX
	{
	public:
		Scene(sf::RenderTarget & target, const TextureHolder & textures);
		~Scene() = default;

	public:
		void createEntity(const std::string & name, Textures::ID texID, const sf::Vector2f & position);
		void destroyEntities();
		void updateSystems(double dt);

	public:
		EntityManager & getEntities();
		Entity getEntity(const std::string & name);

	private:
		void initSystems(sf::RenderTarget & target);

	private:
		EntityManager m_entities;
		EventManager m_events;
		SystemManager m_systems;
		const TextureHolder & m_textures;
	};
}
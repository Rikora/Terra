#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <entityx/entityx.h>
#include <graphics/components/Render.hpp>
#include <graphics/components/Animation.hpp>
#include <graphics/components/BoundingBox.hpp>
#include <graphics/components/Transform.hpp>
#include <graphics/components/PlayerMinion.hpp>
#include <graphics/components/Text.hpp>
#include <utils/ResourceHolder.hpp>
#include <utils/ResourceIdentifiers.hpp>

using namespace entityx;

namespace px
{
	class Scene : public EntityX
	{
	public:
		explicit Scene(sf::RenderTarget & target, TextureHolder & textures, FontHolder & fonts);
		~Scene() = default;

	public:
		Entity createEntity(const std::string & name, Textures::ID texID, const sf::Vector2f & position, const uint & layer = 0);
		Entity createText(const std::string & name, Fonts::ID fontID, const uint & fontSize, const sf::Vector2f & position);
		void createPlayerMonk();
		void destroyEntities();
		void updateRenderSystem(TimeDelta dt);
		void updateTransformSystems(TimeDelta dt);

	public:
		EntityManager & getEntities();
		Entity getEntity(const std::string & name);

	private:
		void initSystems(sf::RenderTarget & target);

	private:
		EntityManager m_entities;
		EventManager m_events;
		SystemManager m_systems;
		TextureHolder & m_textures;
		FontHolder & m_fonts;
		std::vector<uint> m_layers;
	};
}
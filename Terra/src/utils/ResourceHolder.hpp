#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <memory>
#include <assert.h>

// Template class for all kinds of different resources
namespace px
{
	namespace utils
	{
		template<typename Resource, typename Identifier>
		class ResourceHolder
		{
		public:
			void loadResource(Identifier id, const std::string & filename);
			template<typename Parameter>
			void loadResource(Identifier id, const std::string & filename, const Parameter & secondParam);

		public:
			Resource & getResource(Identifier id);
			const Resource & getResource(Identifier id) const;

		private:
			void insertResource(Identifier id, std::unique_ptr<Resource> & resource);

		private:
			std::map<Identifier, std::unique_ptr<Resource>> m_resourceMap;
		};

		template<typename Resource, typename Identifier>
		inline void ResourceHolder<Resource, Identifier>::loadResource(Identifier id, const std::string & filename)
		{
			auto resource = std::make_unique<Resource>();
			if (!resource->loadFromFile(filename))
				throw std::runtime_error("ResourceHolder::loadResource - Failed to load" + filename);

			insertResource(id, resource);
		}

		template<typename Resource, typename Identifier>
		template<typename Parameter>
		inline void ResourceHolder<Resource, Identifier>::loadResource(Identifier id, const std::string & filename, const Parameter & secondParam)
		{
			auto resource = std::make_unique<Resource>();
			if (!resource->loadFromFile(filename, secondParam))
				throw std::runtime_error("ResourceHolder::loadResource - Failed to load" + filename);

			insertResource(id, resource);
		}

		template<typename Resource, typename Identifier>
		inline Resource & ResourceHolder<Resource, Identifier>::getResource(Identifier id)
		{
			auto found = m_resourceMap.find(id);
			assert(found != m_resourceMap.end());

			return *found->second;
		}

		template<typename Resource, typename Identifier>
		inline const Resource & ResourceHolder<Resource, Identifier>::getResource(Identifier id) const
		{
			auto found = m_resourceMap.find(id);
			assert(found != m_resourceMap.end());

			return *found->second;
		}

		template<typename Resource, typename Identifier>
		inline void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> & resource)
		{
			auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
			assert(inserted.second);
		}
	}
}

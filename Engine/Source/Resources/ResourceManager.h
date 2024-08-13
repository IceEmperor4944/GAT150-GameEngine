#pragma once
#include "Resource.h"
#include "Core/Singleton.h"
#include "Core/EString.h"
#include <map>
#include <iostream>

class ResourceManager : public Singleton<ResourceManager> {
public:
	void Clear() { m_resources.clear(); }

	template<typename T, typename ... TArgs>
	res_t<T> Get(const std::string& name, TArgs ... args);

	friend class Singleton;
protected:
	ResourceManager() = default;
private:
	std::map<std::string, res_t<Resource>> m_resources;
};

template<typename T, typename ... TArgs>
inline res_t<T> ResourceManager::Get(const std::string& name, TArgs ... args) {
	std::string nameLower = ToLower(name);

	//find resource in manager
	if (m_resources.find(nameLower) != m_resources.end()) {
		//return resource
		return std::dynamic_pointer_cast<T>(m_resources[nameLower]);
	}

	//resource not found, create resource
	res_t<T> resource = std::make_shared<T>();
	if (!resource->Create(nameLower, args...)) {
		//resource not created
		std::cerr << "Could not create resource: \"" << nameLower << "\"" << std::endl;
		return res_t<T>();
	}

	//add resource to manager
	m_resources[nameLower] = resource;
	return resource;
}
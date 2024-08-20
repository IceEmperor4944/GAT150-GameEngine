#pragma once
#include "Singleton.h"

#include <memory>
#include <map>
#include <string>
#include <iostream>

class CreatorBase {
public:
	virtual ~CreatorBase() = default;
	virtual std::unique_ptr<class Object> Create() = 0;
};

template <typename T>
class Creator : public CreatorBase {
public:
	std::unique_ptr<class Object> Create() override {
		return std::make_unique<T>();
	}
};

template <typename T>
class PrototypeCreator : public CreatorBase {
public:
	PrototypeCreator(std::unique_ptr<T> prototype) : m_prototype{ std::move(prototype) } {}
	std::unique_ptr<class Object> Create() override {
		return m_prototype->Clone();
	}
private:
	std::unique_ptr<T> m_prototype;
};

class Factory : public Singleton<Factory> {
public:
	template <typename T> void Register(const std::string& name);
	template <typename T> void RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype);
	template <typename T> std::unique_ptr<T> Create(const std::string& name);
private:
	std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;
};

template<typename T>
inline void Factory::Register(const std::string& name) {
	m_registry[name] = std::make_unique<Creator<T>>();
}

template<typename T>
inline void Factory::RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype) {
	m_registry[name] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
}

template<typename T>
inline std::unique_ptr<T> Factory::Create(const std::string& name) {
	if (m_registry.find(name) != m_registry.end()) {
		return std::unique_ptr<T>(dynamic_cast<T*>(m_registry[name]->Create().release()));
	}

	std::cerr << "Could not create factory object: \"" << name << "\"" << std::endl;

	return std::unique_ptr<T>();
}
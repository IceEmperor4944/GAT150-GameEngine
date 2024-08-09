#pragma once
#include <string>

#define CLASS_DECLARATION(class) \
	static const char* GetTypeName() { return #class; }

class Object {
public:
	Object() = default;
	Object(const std::string& name) : name{ name } {}
	virtual ~Object() = default;

	virtual void Initialize() = 0;
	virtual void Activate() { isActive = true; }
	virtual void Deactivate() { isActive = false; }
public:
	std::string name;
	bool isActive = false;
};
#pragma once
#include <string>
//DO NOT MAKE ON HEAP OR NEW
//USE GM::CreateActor()
class Actor
{
protected:
	std::string name;

public:
	Actor(std::string name);
	virtual ~Actor();

	virtual void Init() {}

public:
	const std::string& GetName() const;
	virtual void Tick(float deltaTime) = 0;

};
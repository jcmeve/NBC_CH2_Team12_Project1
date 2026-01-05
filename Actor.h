#pragma once
#include <string>
//DO NOT MAKE ON HEAP OR NEW
//USE GM::CreateActor()
class Actor
{
protected:
	std::wstring name;

public:
	Actor(std::wstring name);
	virtual ~Actor();

public:
	const std::wstring& GetName() const;
	void SetName(const std::wstring& _name);
	virtual void Tick(float deltaTime) = 0;

};
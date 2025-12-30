#pragma once
#include <string>
//DO NOT MAKE ON HEAP OR NEW
//USE GM::CreateActor()
class Actor
{
protected:
	std::string name;

	//이름, 초기 체력, 공격력
public:
	Actor(std::string name);
	virtual ~Actor();

public:
	const std::string& GetName() const;
	virtual void Tick(float deltaTime) = 0;

};
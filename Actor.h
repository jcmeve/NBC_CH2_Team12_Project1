#pragma once
#include <string>
//DO NOT MAKE ON HEAP OR NEW
//USE GM::CreateActor()
class Actor
{
protected:
	std::wstring name;

	//이름, 초기 체력, 공격력
public:
	Actor(std::wstring name);
	virtual ~Actor();

public:
	const std::wstring& GetName() const;
	virtual void Tick(float deltaTime) = 0;

};
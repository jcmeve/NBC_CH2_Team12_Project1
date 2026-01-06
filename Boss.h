#pragma once
#include "Monster.h"
class Boss : public Monster {
public:
	Boss(std::wstring name);
	virtual ~Boss();

	void Init(int playerLevel);

};


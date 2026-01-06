#pragma once
#include "Pawn.h"
#include <string>

class Monster : public Pawn
{
public:
	Monster(std::wstring name);
	virtual ~Monster();

	void Init(int playerLevel);
	bool LoadAscii(std::wstring fileName)override;

	int dropGold();
	void TakeDamage(int damage) override;

	bool CanQTE()const;
	void ResetQTETimer();
	// Actor을(를) 통해 상속됨
	void Tick(float deltaTime) override;
private:
	float qteTime;
	float qteTimer;



	// Pawn을(를) 통해 상속됨
	void PlayAudio(EAction action) override;

};
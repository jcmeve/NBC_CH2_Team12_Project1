#pragma once
#include "Actor.h"
#include <map> //for keyState

class Character;
class BattleManager;

enum class GameState
{
	TITLE, //게임 시작 화면
	CREATE_CHARACTER, //캐릭터 생성
	STORY, //스토리 진행
	BATTLE, //전투중
	SHOP, //상점
	BOSS_BATTLE, //레벨 10 달성 시 보스전
	ENDING //엔딩
};

class TextRPG : public Actor {
private:
	GameState currentState = GameState::TITLE;
	Character* player = nullptr;
	BattleManager* battleManager = nullptr;

	std::map<int, bool> keyState;

public:
	TextRPG(std::wstring name);
	virtual ~TextRPG();

	// Actor을(를) 통해 상속됨
	void Tick(float deltaTime) override;

private:
	void UpdateTitle();
	void UpdateCreateCharacter();
	void UpdateStory();
	void UpdateBattle();
	void UpdateShop();
	void UpdateEnding();

	void ChangeState(GameState newState);

	bool isKeyJustPressed(int key);
};


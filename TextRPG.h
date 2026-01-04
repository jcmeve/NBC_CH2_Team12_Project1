#pragma once
#include "Actor.h"

class Character;
class Monster;
class BattleManager;
class Shop;
enum class GameState
{
	TITLE, // 게임 시작 화면
	CREATE_CHARACTER, // 캐릭터 생성
	STORY, // 스토리 진행
	BATTLE, // 전투중
	SHOP, // 상점
	STATUS, // 스탯 및 인벤토리 확인
	BOSS_BATTLE, // 레벨 10 달성 시 보스전
	ENDING // 엔딩
};

class TextRPG : public Actor {
private:
	GameState currentState = GameState::TITLE;
	Character* player = nullptr;
	Monster* currentMonster = nullptr;
	BattleManager* battleManager = nullptr;
	Shop* shop;


	std::wstring inputName = L"";

	bool isInitialized = false;

public:
	TextRPG(std::wstring name);
	virtual ~TextRPG();

	void Tick(float deltaTime) override;

private:
	// 상태 관리 함수
	void EnterState(GameState state);
	void ExitState(GameState state);
	void ChangeState(GameState newState);

	// 각 상태별 로직
	void UpdateTitle();
	void UpdateCreateCharacter();
	void UpdateStory();
	void UpdateBattle();
	void UpdateShop();
	void UpdateStatus();
	void UpdateEnding();

};


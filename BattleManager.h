#pragma once
#include"Actor.h"

class Character;
class Monster;
class Pawn;

enum class BattleState
{
	BS_WAITING, //전투 시작 전 OR 턴 사이 대기
	BS_PLAYER_TURN, //플레이어 행동
	BS_MONSTER_TURN, //몬스터 턴
	BS_VICTORY, //플레이어 승리 (보상)
	BS_DEFEAT, //플레이어 패배 (게임오버)
	BS_REWARD, //보상 확인
	BS_END //전투 종료 
};

class BattleManager : public Actor {
private:
	Character* player = nullptr;
	Monster* monster = nullptr;

	BattleState currentState;
	float turnTimer = 1.0f;
	float turnDelay = 1.0f;
public:
	BattleManager(std::wstring name);
	virtual ~BattleManager();

	void StartBattle(Character* p, Monster* m);
	BattleState GetBattleState() const;

	//spawn monster, drop item when player win
	// Actor을(를) 통해 상속됨
	void Tick(float deltaTime) override;

private:
	void ProcessPlayerTurn();
	void ProcessMonsterTurn();

};


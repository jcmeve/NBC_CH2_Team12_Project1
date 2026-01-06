#pragma once
#include"Actor.h"

class Character;
class Monster;
class Pawn;
class StatWidget;
enum class BattleState
{
	BS_FIGHT, 
	BS_WAIT,//예전에 있던 wate랑 다름 현재는 QTE 전용
	BS_FINISH_DELAY,
	BS_VICTORY, //플레이어 승리 (보상)
	BS_DEFEAT, //플레이어 패배 (게임오버)
	BS_REWARD, //보상 확인
	BS_END //전투 종료 
};

class BattleManager : public Actor {
private:
	Character* player = nullptr;
	Monster* monster = nullptr;

	StatWidget* playerStatWidget;
	StatWidget* monsterStatWidget;


	BattleState currentState;

	float finishTimer = 0.0f;
	float waitTimer = 0.0f;

public:
	BattleManager(std::wstring name);
	virtual ~BattleManager();

	void StartBattle(Character* p, Monster* m);
	BattleState GetBattleState() const;

	//spawn monster, drop item when player win
	void Tick(float deltaTime) override;
	void Exit();

private:
	void ProcessPlayerTurn();
	void ProcessMonsterTurn();

	void ProcessVictory();
	void ProcessDefeat();
};


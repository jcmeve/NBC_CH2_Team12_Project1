#include "BattleManager.h"
#include "Actor.h"
#include "Monster.h"
#include "Character.h"
#include "GameManager.h"


BattleManager::BattleManager(std::wstring name) :Actor(name) {}

BattleManager::~BattleManager() {}

void BattleManager::StartBattle(Character* p, Monster* m)
{
	if (!p || !m)
	{
		return;
	}

	player = p;
	monster = m;
	monster->SetPos(120, 0, false);

	GM::GetLogger().Log(L"=============== 전투 시작! ===============");

	currentState = BattleState::BS_WAITING;
	playerGauge = MAX_GAUGE; //플레이어 선공
	monsterGauge = 0.0;
}

BattleState BattleManager::GetBattleState() const
{
	return currentState;
}

void BattleManager::Tick(float deltaTime)
{
	if (currentState == BattleState::BS_END)
	{
		return;
	}

	if (currentState == BattleState::BS_VICTORY || currentState == BattleState::BS_DEFEAT)
	{
		if (GM::GetInput().IsKeyDown(VK_SPACE))
		{
			currentState = BattleState::BS_END;
		}
	}

	if (currentState == BattleState::BS_FINISH_DELAY)
	{
		//승패 확인 전 딜레이
		finishTimer -= deltaTime;
		if (finishTimer <= 0.0f)
		{
			if (player->IsDead()) ProcessDefeat();
			else if (monster->IsDead()) ProcessVictory();
		}
	}

	if (currentState == BattleState::BS_WAITING)
	{
		playerGauge += player->GetAttackSpeed() * deltaTime;
		monsterGauge += monster->GetAttackSpeed() * deltaTime;

		bool playerReady = playerGauge >= MAX_GAUGE;
		bool monsterReady = monsterGauge >= MAX_GAUGE;

		if (playerReady)
		{
			currentState = BattleState::BS_PLAYER_TURN;
			playerGauge = 0;
		}
		else if (monsterReady)
		{
			currentState = BattleState::BS_MONSTER_TURN;
			monsterGauge = 0;
		}
	}
	else if (currentState == BattleState::BS_PLAYER_TURN)
	{
		ProcessPlayerTurn();
	}
	else if (currentState == BattleState::BS_MONSTER_TURN)
	{
		ProcessMonsterTurn();
	}
}

void BattleManager::ProcessPlayerTurn()
{
	if (player->CanAttack(monster))
	{
		int hpBefore = monster->GetHealth();
		player->Attack(*monster);
		int damage = hpBefore - monster->GetHealth();

		std::wstring log = L"[플레이어 공격] " + monster->GetName() + L"에게 " + std::to_wstring(damage) + L"데미지를 입혔습니다!"
			+ L" (남은 체력: " + std::to_wstring(monster->GetHealth()) + L")";
		GM::GetLogger().Log(log);
	}

	if (monster->IsDead())
	{
		finishTimer = 1.5f;
		currentState = BattleState::BS_FINISH_DELAY;
	}
	else
	{
		currentState = BattleState::BS_WAITING;
	}
}

void BattleManager::ProcessMonsterTurn()
{
	if (monster->CanAttack(player))
	{
		int hpBefore = player->GetHealth();
		monster->Attack(*player);
		int damage = hpBefore - player->GetHealth();

		std::wstring log = L"[몬스터 공격] " + player->GetName() + L"에게 " + std::to_wstring(damage) + L"데미지를 입혔습니다!"
			+ L" (남은 체력: " + std::to_wstring(player->GetHealth()) + L")";
		GM::GetLogger().Log(log);
	}

	if (player->IsDead())
	{
		finishTimer = 1.5f;
		currentState = BattleState::BS_FINISH_DELAY;
	}
	else
	{
		currentState = BattleState::BS_WAITING;
	}
}

void BattleManager::ProcessVictory()
{
	GM::GetLogger().Log(L"전투 승리! 몬스터를 처치했습니다.");
	player->RecordKill(monster->GetName());
	player->addExperience(50);
	player->addGold(monster->dropGold());
	//아이템 획득 추가 필요

	player->ShowKillLog();
	GM::GetLogger().Log(L"[Space bar] 계속 진행");

	currentState = BattleState::BS_VICTORY;
}

void BattleManager::ProcessDefeat()
{
	GM::GetLogger().Log(L"전투에서 패배했습니다...");

	currentState = BattleState::BS_DEFEAT;
}
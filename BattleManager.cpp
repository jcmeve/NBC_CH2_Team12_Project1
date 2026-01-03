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

	GM::GetLogger().Log(L"=============== 전투 시작! ===============");

	currentState = BattleState::BS_PLAYER_TURN;
	turnTimer = 0.0f;
	turnDelay = 1.0f;
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

	if (turnTimer > 0.0f)
	{
		turnTimer -= deltaTime;
		return;
	}

	switch (currentState)
	{
	case BattleState::BS_PLAYER_TURN:
		ProcessPlayerTurn();
		break;

	case BattleState::BS_MONSTER_TURN:
		ProcessMonsterTurn();
		break;
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
		GM::GetLogger().Log(L"전투 승리! 몬스터를 처치했습니다.");
		player->addExperience(50);
		player->addGold(monster->dropGold());
		GM::GetLogger().Log(L"[Space bar] 계속 진행");
		currentState = BattleState::BS_VICTORY;
	}
	else
	{
		currentState = BattleState::BS_MONSTER_TURN;
		turnTimer = turnDelay / player->GetAttackSpeed();
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
		GM::GetLogger().Log(L"전투에서 패배했습니다...");
		currentState = BattleState::BS_DEFEAT;
	}
	else
	{
		currentState = BattleState::BS_PLAYER_TURN;
		turnTimer = turnDelay / monster->GetAttackSpeed();
	}
}
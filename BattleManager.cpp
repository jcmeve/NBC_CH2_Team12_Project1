#include "BattleManager.h"
#include "Actor.h"
#include "Monster.h"
#include "Character.h"
#include "GameManager.h"


BattleManager::BattleManager(std::wstring name) :Actor(name) {}

BattleManager::~BattleManager()
{
}

void BattleManager::StartBattle(Character* p, Monster* m)
{
	if (!p || !m)
	{
		return;
	}

	player = p;
	monster = m;

	GM::GetLogger().Log(L"=============== 전투 시작! ===============");

	CurrentState = BattleState::BS_PLAYER_TURN;
	turnTimer = 1.0f;
	turnDelay = 1.0f;
}

BattleState BattleManager::GetBattleState() const
{
	return CurrentState;
}

void BattleManager::Tick(float deltaTime)
{
	if (CurrentState == BattleState::BS_END ||
		CurrentState == BattleState::BS_VICTORY ||
		CurrentState == BattleState::BS_DEFEAT)
	{
		return;
	}

	if (turnTimer > 0.0f)
	{
		turnTimer -= deltaTime;
		return;
	}

	switch (CurrentState)
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
	if (CanAttack(player, monster))
	{
		int hpBefore = monster->GetHealth();
		player->Attack(*monster);
		int damage = hpBefore - monster->GetHealth();

		std::wstring log = L"[플레이어 공격]" + monster->GetName() + L"에게" + std::to_wstring(damage) + L"데미지를 입혔습니다!"
			+ L"(남은 체력: " + std::to_wstring(monster->GetHealth()) + L")";
		GM::GetLogger().Log(log);
	}

	if (monster->IsDead())
	{
		GM::GetLogger().Log(L"전투 승리! 몬스터를 처치했습니다.");
		CurrentState = BattleState::BS_VICTORY;
	}
	else
	{
		CurrentState = BattleState::BS_MONSTER_TURN;
		turnTimer = turnDelay;
	}
}

void BattleManager::ProcessMonsterTurn()
{
	if (CanAttack(monster, player))
	{
		int hpBefore = player->GetHealth();
		monster->Attack(*player);
		int damage = hpBefore - player->GetHealth();

		std::wstring log = L"[몬스터 공격]" + player->GetName() + L"에게" + std::to_wstring(damage) + L"데미지를 입혔습니다!"
			+ L"(남은 체력: " + std::to_wstring(player->GetHealth()) + L")";
		GM::GetLogger().Log(log);
	}

	if (player->IsDead())
	{
		GM::GetLogger().Log(L"전투에서 패배했습니다...");
		CurrentState = BattleState::BS_DEFEAT;
	}
	else
	{
		CurrentState = BattleState::BS_PLAYER_TURN;
		turnTimer = turnDelay;
	}
}

bool BattleManager::CanAttack(Pawn* attacker, Pawn* target)
{
	if (!attacker || !target)
	{
		return false;
	}

	if (attacker->IsDead() || target->IsDead())
	{
		return false;
	}

	return true;
}

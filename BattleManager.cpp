#include "BattleManager.h"
#include "Actor.h"
#include "Monster.h"
#include "Character.h"
#include "Utilities.h"
#include "Inventory.h"
#include "GameManager.h"
#include "StatWidget.h"
#include "QTE.h"
BattleManager::BattleManager(std::wstring name) :Actor(name) {}
BattleManager::~BattleManager() {

}
void BattleManager::Exit() {
	GM::DestroyActor(playerStatWidget);
	playerStatWidget = nullptr;
	GM::DestroyActor(monsterStatWidget);
	monsterStatWidget = nullptr;
}

void BattleManager::StartBattle(Character* p, Monster* m)
{
	if (!p || !m)
	{
		return;
	}

	player = p;
	monster = m;
	monster->SetPos(120, 0, false);
	
	player->ReCalc();
	monster->ReCalc();

	player->InitAttackTimer();
	monster->InitAttackTimer();

	playerStatWidget = GM::CreateActor<StatWidget>(player->GetName());
	playerStatWidget->SetTarget(player);
	playerStatWidget->Init(0, 0, 20, 10);
	monsterStatWidget = GM::CreateActor<StatWidget>(monster->GetName());
	monsterStatWidget->SetTarget(monster);
	monsterStatWidget->Init(120, 0, 20, 10);


	GM::GetLogger().Log(L"=============== 전투 시작! ===============");

	currentState = BattleState::BS_FIGHT;
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

	if (currentState == BattleState::BS_FIGHT)
	{
		if (player->CanAttack(monster)) {
			ProcessPlayerTurn();
		}
		if (monster->CanAttack(player)) {
			ProcessMonsterTurn();
		}
	}

}

void BattleManager::ProcessPlayerTurn()
{
	// 랜덤 아이템 사용 시도
	int randomValue = Utilities::GenerateRandomValue(0, 50);

	if (randomValue < 50)
	{
		player->TryUseRandomItem();
	}

	// 공격

	int hpBefore = monster->GetHealth();
	player->Attack(*monster);
	int damage = hpBefore - monster->GetHealth();

	std::wstring log = L"[플레이어 공격] " + monster->GetName() + L"에게 " + std::to_wstring(damage) + L"데미지를 입혔습니다!"
		+ L" (남은 체력: " + std::to_wstring(monster->GetHealth()) + L")";
	GM::GetLogger().Log(log);
	

	if (monster->IsDead())
	{
		finishTimer = 1.5f;
		currentState = BattleState::BS_FINISH_DELAY;
	}

}

void BattleManager::ProcessMonsterTurn()
{
	//QTE* qte = GM::CreateActor<QTE>(L"TESTQTE");
	//qte->Init(player, 3);
	//QTE TEST

	int hpBefore = player->GetHealth();
	monster->Attack(*player);
	int damage = hpBefore - player->GetHealth();

	std::wstring log = L"[몬스터 공격] " + player->GetName() + L"에게 " + std::to_wstring(damage) + L"데미지를 입혔습니다!"
		+ L" (남은 체력: " + std::to_wstring(player->GetHealth()) + L")";
	GM::GetLogger().Log(log);


	if (player->IsDead())
	{
		finishTimer = 1.5f;
		currentState = BattleState::BS_FINISH_DELAY;
	}

}

void BattleManager::ProcessVictory()
{
	GM::GetLogger().Log(L"전투 승리! 몬스터를 처치했습니다.");
	player->RecordKill(monster->GetName());
	player->addExperience(50);
	player->addGold(monster->dropGold());

	// 아이템 획득
	int itemDropChance = Utilities::GenerateRandomValue(0, 99);
	if (itemDropChance < 100) // 디버그용
	{
		std::vector<Item*> allItems = GM::GetItemManager().GetAllItems();
		if (!allItems.empty())
		{
			int idx = Utilities::GenerateRandomValue(0, allItems.size() - 1);
			const Item* dropItem = allItems[idx];
			player->getInventory()->AddItem(dropItem);

			GM::GetLogger().Log(L"아이템을 획득했습니다! [" + dropItem->GetName() + L"]");
		}
	}

	// 업적 알림
	GM::GetAchievement().NotifyBattleWin();

	player->ShowKillLog();
	GM::GetLogger().Log(L"[Space bar] 계속 진행");

	currentState = BattleState::BS_VICTORY;
}

void BattleManager::ProcessDefeat()
{
	GM::GetLogger().Log(L"전투에서 패배했습니다...");

	currentState = BattleState::BS_DEFEAT;
}
#include "Character.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemManager.h"
#include "GameManager.h"
#include "Artifact.h"
#include "Equipment.h"
#include "UsableItem.h"

Character::Character(std::wstring name) :
	Pawn(name, 0, 0, 0, 1.0f), level(1), experience(0), gold(0)
{
}

Character::~Character() {}

void Character::Init()
{
	Pawn::Init();
	this->level = 1;
	this->maxHealth = 200;
	this->health = maxHealth;
	this->dmg = 30;
	this->def = 10; //기본 방어력 10, 레벨업마다 5 증가
	this->attackSpeed = 50.0f;
	this->experience = 0;
	this->gold = 123450;

	this->inventory = std::make_unique<Inventory>();

	GM::GetLogger().Log(L"플레이어 초기화 완료!");
}

void Character::TakeDamage(int damage)
{
	Pawn::TakeDamage(damage);
}

void Character::displayStatus()
{
	GM::GetLogger().Log(L"=============== Player's Status ===============\n");
	GM::GetLogger().Log(L"이름: " + name);
	GM::GetLogger().Log(L"레벨: " + std::to_wstring(level) + L" | 경험치: " + std::to_wstring(experience) + L"/100");
	GM::GetLogger().Log(L"현재 체력: " + std::to_wstring(health) + L"/" + std::to_wstring(maxHealth));
	GM::GetLogger().Log(L"방어력: " + std::to_wstring(def));
	GM::GetLogger().Log(L"소지 골드: " + std::to_wstring(gold));
}

void Character::levelUp()
{
	level++;
	ReCalc();
	health = maxHealth;

	GM::GetAchievement().NotifyLevelUp(level);
}

bool Character::TryUseRandomItem()
{
	const UsableItem* usableItem = inventory->PopRandomUsableItem();

	if (usableItem == nullptr)
	{
		return false;
	}

	GM::GetLogger().Log(name + L"이(가) 아이템 " + usableItem->GetName() + L"을(를) 사용했습니다!");
	usableItem->Use(*this);

	return true;
}

Inventory* Character::getInventory() const
{
	return inventory.get();
}

int Character::getLevel() const
{
	return level;
}

int Character::getExperience() const
{
	return experience;
}

int Character::getGold() const
{
	return gold;
}

void Character::addExperience(int exp)
{
	experience += exp;
	GM::GetLogger().Log(L"경험치 +" + std::to_wstring(exp) + L" 획득! (현재: " + std::to_wstring(experience) + L"/100)");

	while (experience >= 100 && level < 10)
	{
		experience -= 100;
		levelUp();
		GM::GetLogger().Log(L"레벨 업! 현재 레벨: " + std::to_wstring(level));
	}
}

void Character::addGold(int amount)
{
	gold += amount;
	GM::GetLogger().Log(L"골드 " + std::to_wstring(amount) + L" 획득! (현재: " + std::to_wstring(gold) + L"G)");

	GM::GetAchievement().NotifyGoldChange(gold);
}

void Character::RemoveGold(int amount) {
	gold -= amount;
	if (gold < 0) {
		GM::GetLogger().ErrorLog(L"Minus GOLD!");
	}
}

void Character::RecordKill(std::wstring monsterName)
{
	killRecord[monsterName]++;
}

void Character::ShowKillLog()
{
	GM::GetLogger().Log(L"=============== 전투 통계 ===============");
	if (killRecord.empty())
	{
		GM::GetLogger().Log(L"기록이 없습니다.");
		return;
	}

	for (auto const& pair : killRecord)
	{
		std::wstring monsterName = pair.first;
		int killCount = pair.second;
		GM::GetLogger().Log(monsterName + L": " + std::to_wstring(killCount));
	}
}

void Character::ReCalc() {
	//발제문서에 써진건 누적같은데 애매한듯
	maxHealth = 200 + (level - 1) * 20;
	originDmg = 30 + (level - 1) * 5;
	originDef = (level - 1) * 5;
	def = originDef;
	dmg = originDmg;


	Pawn::ReCalc();

	const std::map<const Artifact*, int, ItemPointerCompare>& artifacts = inventory->GetArtifacts();
	for (const auto& pair : artifacts) {
		pair.first->ReCalc(*this);
	}


}

void Character::Tick(float deltaTime) {
	Pawn::Tick(deltaTime);
}

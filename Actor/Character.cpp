#include "Character.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemManager.h"
#include "GameManager.h"
#include "Artifact.h"
#include "Equipment.h"
#include "UsableItem.h"
#include "Buff.h"

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
	this->attackSpeed = 0.5;
	this->experience = 0;
	this->gold = 1111110;

	equipmentSlot.assign(equipmentSlotSize, nullptr);

	this->inventory = std::make_unique<Inventory>();

	GM::GetLogger().Log(L"플레이어 초기화 완료!");
}

bool Character::LoadAscii(std::wstring fileName) {

	for (int chapter = 0; chapter < 4; ++chapter) {
		for (EAction action : {EAction::IDLE1, EAction::IDLE2, EAction::ATTACK, EAction::DEFENSE }) {
			std::wstring buf;
			GM::GetSave().LoadAscii(L"Player\\Player0" + std::to_wstring(chapter + 1) + L"_" + EActionToString(action), buf);
			ascii[action].push_back(buf);
		}
	}

	return true;
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

bool Character::addExperience(int exp)
{
	experience += exp;
	//GM::GetLogger().Log(L"경험치 +" + std::to_wstring(exp) + L" 획득! (현재: " + std::to_wstring(experience) + L"/100)");

	while (experience >= 100 && level < 10)
	{
		experience -= 100;
		levelUp();
		//GM::GetLogger().Log(L"레벨 업! 현재 레벨: " + std::to_wstring(level));
		return true;
	}
	return false;
}

void Character::addGold(int amount)
{
	gold += amount;
	//GM::GetLogger().Log(L"골드 " + std::to_wstring(amount) + L" 획득! (현재: " + std::to_wstring(gold) + L"G)");

	GM::GetAchievement().NotifyGoldChange(gold);
}

void Character::RemoveGold(int amount) {
	gold -= amount;
	if (gold < 0) {
		GM::GetLogger().ErrorLog(L"Minus GOLD!");
	}
}

void Character::PlayAudio(EAction action) {
	if (action == EAction::DIE)
		return;
	if (action == EAction::ATTACK || action == EAction::HIT || action == EAction::USEITEM || action == EAction::EQUIP) {
		GM::GetSound().PlayAudio(L"Player_" + EActionToString(action) + std::to_wstring(Utilities::GenerateRandomValue(1, 2)));
	}
	//else i{
	//    GM::GetSound().PlayAudio(L"Player_" + EActionToString(action));
	//}

}

std::wstring Character::GetKillLogText() const
{
	if (killRecord.empty())
	{
		return L"기록된 전투가 없습니다.";
	}

	std::wstring text = L"";

	for (auto const& pair : killRecord)
	{
		std::wstring monsterName = pair.first;
		int killCount = pair.second;
		text += monsterName + L" : " + std::to_wstring(killCount) + L" 마리\n";
	}

	return text;
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
	for (const auto& i : equipmentSlot) {
		if(i)
			i->ReCalc(*this);
	}

	if (health > maxHealth) {
		health = maxHealth;
	}

}

bool Character::Equip(const Equipment* equipment) {
	for (int i = 0; i < equipmentSlot.size(); ++i) {
		if (equipmentSlot[i] == nullptr) {
			equipmentSlot[i] = equipment;
			inventory->RemoveItem(equipment);
			PlayAudio(EAction::EQUIP);
			ReCalc();
			return true;
		}
	}
	return false;

}

void Character::Unequip(int idx) {
	if (idx >= equipmentSlot.size() || idx < 0) {
		return;
	}
	if (equipmentSlot[idx] == nullptr) {
		return;
	}
	PlayAudio(EAction::EQUIP);
	inventory->AddItem(equipmentSlot[idx]);
	equipmentSlot[idx] = nullptr;
	ReCalc();

}

const Equipment* Character::GetCurrentEquipment(int idx) {
	if (idx >= equipmentSlot.size())
		return nullptr;
	return equipmentSlot[idx];
}

int Character::GetCurrentEquipmentSize() {
	return equipmentSlot.size();
}

void Character::Tick(float deltaTime) {
	Pawn::Tick(deltaTime);

	int chapter = 0;
	if (level < 4) chapter = 1;
	else if (level < 7) chapter = 2;
	else if (level < 10) chapter = 3;
	else chapter = 4;


	if (!isVisible) {
		return;
	}
	if (isAttacking) {
		GM::GetDisplay().DrawAscii(ascii[EAction::ATTACK][chapter - 1], posX, posY);
		return;
	}

	if (!IsDead()) {
		if (idleMotionIdx == 0) {
			GM::GetDisplay().DrawAscii(ascii[EAction::IDLE1][chapter - 1], posX, posY);
		}
		else if (idleMotionIdx == 1) {
			GM::GetDisplay().DrawAscii(ascii[EAction::IDLE2][chapter - 1], posX, posY);
		}
	}

}

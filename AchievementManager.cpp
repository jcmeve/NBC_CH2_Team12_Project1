#include "AchievementManager.h"
#include "GameManager.h"


AchievementManager::AchievementManager() {}
AchievementManager::~AchievementManager() {}


void AchievementManager::init()
{
	achievements.resize((int)AchievementID::MAX);

	achievements[0] = Achievement(AchievementID::FIRST_STEP, L"첫 발걸음", L"구원의 시작", L"재앙의 시작", L"첫 전투 승리");
	achievements[1] = Achievement(AchievementID::PURIFIER, L"정화자", L"세계가 조금씩 깨끗해진다", L"5명의 생존자 사망", L"5회 전투 승리");
	achievements[2] = Achievement(AchievementID::SAVIOR, L"구원자", L"당신은 영웅이다", L"학살자", L"10회 전투 승리");
	achievements[3] = Achievement(AchievementID::PERFECTION, L"완벽한 존재", L"진화의 끝", L"완벽한 재앙", L"레벨 10 달성");
	achievements[4] = Achievement(AchievementID::SILENCE, L"침묵의 세계", L"평화가 찾아왔다", L"아무도 남지 않았다", L"게임 클리어");
	achievements[5] = Achievement(AchievementID::COLLECTOR, L"수집가", L"만반의 준비", L"탐욕의 끝", L"모든 아이템 획득");
	achievements[6] = Achievement(AchievementID::RICH, L"부자", L"경제의 중심", L"약탈자", L"골드 300 달성");
	achievements[7] = Achievement(AchievementID::SURVIVOR, L"생존자", L"불굴의 의지", L"죽음을 거부한 자", L"사망 없이 10회 전투");
}


void AchievementManager::OnNewGame()
{
	battleWinCount = 0;
	hasDied = false;
}

const Achievement& AchievementManager::GetAchievement(AchievementID id) const
{
	if ((int)id < 0 || (int)id >= (int)AchievementID::MAX)
	{
		static Achievement dummy;
		return dummy; // 반환값이 참조라 null 불가능
	}

	return achievements[(int)id];
}

void AchievementManager::Unlock(AchievementID id)
{
	int index = (int)id;

	if (index < 0 || index >= (int)AchievementID::MAX)
	{
		return;
	}

	if (achievements[index].isUnlocked)
	{
		return;
	}

	achievements[index].isUnlocked = true;

	GM::GetLogger().Log(L"========================================");
	GM::GetLogger().Log(L"           업적을 달성했습니다!         ");
	GM::GetLogger().Log(L"========================================");

	GM::GetLogger().Log(L"[" + achievements[index].fakeTitle + L"] " + achievements[index].fakeDesc);
	GM::GetLogger().Log(achievements[index].unlockCondition);
	GM::GetLogger().Log(L"========================================");
}

// ==========================================================
// 이벤트 핸들러
// ==========================================================


void AchievementManager::NotifyBattleWin()
{
	battleWinCount++;
	if (battleWinCount >= 1)
	{
		Unlock(AchievementID::FIRST_STEP);
	}
	if (battleWinCount >= 5)
	{
		Unlock(AchievementID::PURIFIER);
	}
	if (battleWinCount >= 10)
	{
		Unlock(AchievementID::SAVIOR);
	}
	if (!hasDied && battleWinCount >= 10)
	{
		Unlock(AchievementID::SURVIVOR);
	}
}

void AchievementManager::NotifyLevelUp(int level)
{
	if (level >= 10)
	{
		Unlock(AchievementID::PERFECTION);
	}
}

void AchievementManager::NotifyGoldChange(int currentGold)
{
	if (currentGold >= 300)
	{
		Unlock(AchievementID::RICH);
	}
}

void AchievementManager::NotifyGameClear()
{
	Unlock(AchievementID::SILENCE);
}

void AchievementManager::NotifyPlayerDied()
{
	hasDied = true;
}

void AchievementManager::NotifyItemCollected(const std::wstring& itemName)
{
	collectedItemNames.insert(itemName);

	int currentCount = (int)collectedItemNames.size(); // 현재 수집한 아이템 개수
	int totalItemCount = GM::GetItemManager().GetTotalItemCount();

	if (currentCount >= totalItemCount && totalItemCount > 0)
	{
		Unlock(AchievementID::COLLECTOR);
	}
}


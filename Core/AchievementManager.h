#pragma once
#include <string>
#include <vector>
#include <set>

enum class AchievementID
{
	FIRST_STEP, // 첫 발걸음
	PURIFIER, // 정화자 (5승)
	SAVIOR, // 구원자 (10승)
	PERFECTION, // 완벽한 존재 (레벨 10 달성)
	SILENCE, // 침묵의 세계 (게임 클리어)
	COLLECTOR, // 수집가 (모든 아이템 획득)
	RICH, // 부자 (300골드)
	SURVIVOR, // 생존자 (사망 없이 10승)
	MAX // 업적 개수 (8)
};

struct Achievement
{
	AchievementID id;
	std::wstring fakeTitle; // 업적 이름 (첫 발걸음)
	std::wstring fakeDesc; // 가짜 설명 (구원의 시작)
	std::wstring trueTitle; // 실제 업적 이름 (재앙의 시작)
	std::wstring unlockCondition; // 달성 조건 (첫 전투 승리)
	bool isUnlocked;

	Achievement() : id(AchievementID::MAX), isUnlocked(false) {}
	Achievement(AchievementID id, std::wstring fakeTitle, std::wstring fakeDesc, std::wstring trueTitle, std::wstring unlockCondition)
		: id(id), fakeTitle(fakeTitle), fakeDesc(fakeDesc), trueTitle(trueTitle), unlockCondition(unlockCondition), isUnlocked(false) {
	}
};

class AchievementManager
{
private:
	AchievementManager();
	~AchievementManager();
	AchievementManager& operator=(const AchievementManager& other) = delete;
	AchievementManager(const AchievementManager& other) = delete;
	AchievementManager& operator=(const AchievementManager&& other) = delete;
	AchievementManager(const AchievementManager&& other) = delete;
	friend class GameManager;

private:
	std::vector<Achievement> achievements;
	std::set<std::wstring> collectedItemNames; // 획득한 아이템 이름 목록 (중복 제거)
	int battleWinCount = 0;
	int totalGold = 0;
	bool hasDied = false;

	void Unlock(AchievementID id);

public:
	void init();
	void OnNewGame();

	void NotifyBattleWin();
	void NotifyLevelUp(int level);
	void NotifyGoldChange(int currentGold);
	void NotifyGameClear();
	void NotifyItemCollected(const std::wstring& itemName);
	void NotifyPlayerDied();

	const Achievement& GetAchievement(AchievementID id) const;
	int GetCount() const { return (int)AchievementID::MAX; }

	std::wstring GetTrueEndingText() const;
};


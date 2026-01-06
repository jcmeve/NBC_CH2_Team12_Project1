#include <Windows.h>
#include "TextRPG.h"
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "Boss.h"
#include "BattleManager.h"
#include<string>
#include "Widget.h"
#include "QTE.h"
#include "InputManager.h"
#include "Shop.h"
#include "Utilities.h"
#include "StoryManager.h"

//   QTE* qte = GM::CreateActor<QTE>(L"QTE TEST");
//   qte->Init(nullptr, 3);

TextRPG::TextRPG(std::wstring name) : Actor(name)
{
	EnterState(GameState::TITLE);
	shop = new Shop();

	gameProgress = 0;
	currentBattleCount = 0;
	canUseShop = false;
}

TextRPG::~TextRPG() {
	shop->Exit();
	delete shop;
}

void TextRPG::Tick(float deltaTime) {
	switch (currentState)
	{
	case GameState::TITLE:
		UpdateTitle();
		break;
	case GameState::CREATE_CHARACTER:
		UpdateCreateCharacter();
		break;
	case GameState::STORY:
		UpdateStory();
		break;
	case GameState::BATTLE:
		UpdateBattle();
		break;
	case GameState::BOSS_BATTLE:
		UpdateBossBattle();
		break;
	case GameState::SHOP:
		UpdateShop(deltaTime);
		break;
	case GameState::STATUS:
		UpdateStatus();
		break;
	case GameState::ENDING:
		UpdateEnding();
		break;
	default:
		break;
	}

}

// ==========================================================
// 상태 변경 시스템
// ==========================================================

void TextRPG::ChangeState(GameState newState)
{
	ExitState(currentState);
	currentState = newState;
	EnterState(currentState);
}

void TextRPG::EnterState(GameState state)
{
	GM::GetDisplay().ClearTextArea();

	switch (state)
	{
	case GameState::TITLE:
		GM::GetLogger().Log(L"==========================");
		GM::GetLogger().Log(L"LAST CLEANER");
		GM::GetLogger().Log(L"==========================");
		GM::GetLogger().Log(L"[Space bar] 게임 시작");
		break;

	case GameState::CREATE_CHARACTER:
		GM::GetLogger().Log(L"당신의 이름을 입력해주세요. *영문 대문자");
		GM::GetLogger().Log(L"[ENTER] 결정");

		break;

	case GameState::STORY:
		// 해당 구역 스토리 로드 (전투 횟수가 0인 경우에만)
		if (currentBattleCount == 0)
		{
			LoadStoryForCurrentProgress();
		}
		else
		{
			GM::GetLogger().Log(L"========================================");
			GM::GetLogger().Log(L"현재 구역 진행도: 전투 " + std::to_wstring(currentBattleCount)
				+ L" / " + std::to_wstring(GetRequiredBattleCount()));
			GM::GetLogger().Log(L"[B] 전투");
			GM::GetLogger().Log(L"[I] 상태창");

			if (canUseShop)
			{
				GM::GetLogger().Log(L"[S] 상점");
			}
		}
		break;

	case GameState::SHOP:
		shop->Enter(player);
		break;

	case GameState::STATUS:
		player->displayStatus();
		GM::GetLogger().Log(L"[ESC] 나가기");
		break;

	case GameState::ENDING:
		GM::GetLogger().Log(L"게임을 클리어했습니다.");
		break;
	}
}

void TextRPG::ExitState(GameState state)
{
	switch (state)
	{
	case GameState::TITLE:
		break;
	case GameState::CREATE_CHARACTER:
		break;
	case GameState::STORY:
		break;
	case GameState::BATTLE:
		//updatebattle에서 옮겨옴
		battleManager->Exit();

		GM::DestroyActor(battleManager);
		battleManager = nullptr;

		GM::DestroyActor(currentMonster);
		currentMonster = nullptr;
		player->ClearBuff();
		player->Heal(player->GetMaxHealth());
		break;

	case GameState::SHOP:
		shop->Exit();
		break;
	case GameState::STATUS:
		break;
	case GameState::BOSS_BATTLE:
		battleManager->Exit();

		GM::DestroyActor(battleManager);
		battleManager = nullptr;

		GM::DestroyActor(currentMonster);
		currentMonster = nullptr;
		player->ClearBuff();
		player->Heal(player->GetMaxHealth());

		break;
	case GameState::ENDING:
		break;
	default:
		break;
	}
}

// ==========================================================
// 각 상태별 로직
// ==========================================================

void TextRPG::UpdateTitle()
{
	if (GM::GetInput().IsKeyDown(VK_SPACE))
	{
		ChangeState(GameState::CREATE_CHARACTER);
		//ChangeState(GameState::STORY);
	}
}

void TextRPG::UpdateCreateCharacter()
{
	// 이름 입력 로직
	for (int key = 'A'; key <= 'Z'; ++key)
	{
		if (GM::GetInput().IsKeyDown(key))
		{
			if (inputName.length() < 10)
			{
				inputName += (wchar_t)key;
			}
		}
	}

	if (GM::GetInput().IsKeyDown(VK_BACK))
	{
		if (!inputName.empty())
		{
			inputName.pop_back();
		}
	}

	if (GM::GetInput().IsKeyDown(VK_RETURN))
	{
		if (inputName.empty())
		{
			GM::GetLogger().Log(L"이름을 입력해주세요!");
		}
		else
		{
			player = GM::CreateActor<Character>(inputName);
			player->Init();
			player->SetVisible(false);
			GM::GetLogger().Log(L"캐릭터 생성 완료!");
			GM::GetStory().SetPlayer(player); // StoryManager 등록

			gameProgress = 1; // 1구역 시작
			currentBattleCount = 0;
			ChangeState(GameState::STORY);
			return;
		}
	}

	std::wstring displayName = inputName + L"_";
	GM::GetDisplay().DrawWidget(30, 10, 20, 5, L"이름", displayName);
}

void TextRPG::UpdateStory()
{
	// StoryManager 실행중 ===========================
	if (!GM::GetStory().IsStoryFinished())
	{
		GM::GetStory().Tick(0.016f);
		return;
	}

	// 스토리 끝남 OR 이미 본 상태 ===================
	// 프롤로그
	if (gameProgress == 0) {
		if (GM::GetInput().IsKeyDown(VK_SPACE))
		{
			ChangeState(GameState::CREATE_CHARACTER);
			gameProgress = 1;
			currentBattleCount = 0;
		}
		return;
	}

	// 게임 진행
	if (GM::GetInput().IsKeyDown('B'))
	{
		// 레벨 10 이상이면 보스전

		if (player->getLevel() >= 10) {
			Boss* temp = GM::CreateActor<Boss>(bossName);
			temp->Init(player->getLevel());
			currentMonster = temp;
			temp = nullptr;
			battleManager = GM::CreateActor<BattleManager>(L"BattleManager");
			battleManager->StartBattle(player, currentMonster);
			ChangeState(GameState::BOSS_BATTLE);
		}
		else {
			int idx = Utilities::GenerateRandomValue(0, monsterNames.size() - 1);
			currentMonster = GM::CreateActor<Monster>(monsterNames[idx]);
			currentMonster->Init(player->getLevel());
			battleManager = GM::CreateActor<BattleManager>(L"BattleManager");
			battleManager->StartBattle(player, currentMonster);

			ChangeState(GameState::BATTLE);

		}
		canUseShop = false;
	}
	else if (canUseShop && GM::GetInput().IsKeyDown('S'))
	{
		ChangeState(GameState::SHOP);
	}
	else if (GM::GetInput().IsKeyDown('I'))
	{
		ChangeState(GameState::STATUS);
	}
}

void TextRPG::UpdateBattle()
{
	if (battleManager == nullptr)
	{
		ChangeState(GameState::STORY);
		return;
	}

	if (battleManager->GetBattleState() != BattleState::BS_END)
	{
		return;
	}

	if (player->IsDead())
	{
		GM::GetLogger().Log(L"타이틀 화면으로 돌아갑니다.");
		ChangeState(GameState::TITLE); // 또는 GameState::GAME_OVER
	}
	else
	{
		currentBattleCount++;
		canUseShop = true;

		int requiredBattleCount = GetRequiredBattleCount();

		GM::GetLogger().Log(L"전투 종료! 현재 진행도: " + std::to_wstring(currentBattleCount)
			+ L"/" + std::to_wstring(requiredBattleCount));

		if (currentBattleCount >= requiredBattleCount)
		{
			GM::GetLogger().Log(L"이 구역의 모든 위협을 제거했습니다. 다음 구역으로 이동합니다!");
			gameProgress++;
			currentBattleCount = 0;
		}

		ChangeState(GameState::STORY);
	}
}


void TextRPG::UpdateBossBattle() {
	if (battleManager == nullptr)
	{
		ChangeState(GameState::STORY);
		return;
	}

	if (battleManager->GetBattleState() != BattleState::BS_END)
	{
		return;
	}

	if (player->IsDead())
	{
		GM::GetLogger().Log(L"타이틀 화면으로 돌아갑니다.");
		ChangeState(GameState::TITLE); // 또는 GameState::GAME_OVER
	}
	else
	{
		ChangeState(GameState::ENDING);
	}
}


void TextRPG::UpdateShop(float deltaTime)
{
	if (GM::GetInput().IsKeyDown(VK_ESCAPE))
	{
		ChangeState(GameState::STORY);
	}
	shop->Tick(deltaTime);
}

void TextRPG::UpdateStatus()
{
	if (GM::GetInput().IsKeyDown(VK_ESCAPE))
	{
		ChangeState(GameState::STORY);
	}
}

void TextRPG::UpdateEnding()
{
	// 엔딩 크레딧 & 게임 종료 처리
}

void TextRPG::LoadStoryForCurrentProgress()
{
	std::wstring filename;
	switch (gameProgress)
	{
	case 0: filename = L"Story_Intro"; break;
	case 1: filename = L"Story_Zone1"; break;
	case 2: filename = L"Story_Zone2"; break;
	case 3: filename = L"Story_Zone3"; break;
	case 4: filename = L"Story_Boss_Intro"; break;
	case 5: filename = L"Story_Ending"; break;
	}

	GM::GetLogger().Log(L"스토리 로드: " + filename);
	GM::GetStory().LoadChapter(filename);
}

int TextRPG::GetRequiredBattleCount() const
{
	switch (gameProgress)
	{
	case 1:
		return 6; // 1구역: 6회
	case 2:
		return 8; // 2구역: 8회
	case 3:
		return 4; // 3구역: 4회
	default:
		return 1;
	}
}
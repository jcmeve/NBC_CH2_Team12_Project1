#include <Windows.h>
#include "TextRPG.h"
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "BattleManager.h"
#include<string>
#include "Widget.h"
#include "QTE.h"
#include "InputManager.h"

//   QTE* qte = GM::CreateActor<QTE>(L"QTE TEST");
//   qte->Init(nullptr, 3);

TextRPG::TextRPG(std::wstring name) : Actor(name)
{
	EnterState(GameState::TITLE);
}

TextRPG::~TextRPG() {}

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
	case GameState::SHOP:
		UpdateShop();
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
	switch (state)
	{
	case GameState::TITLE:
		GM::GetLogger().Log(L"==========================");
		GM::GetLogger().Log(L"LAST CLEANER");
		GM::GetLogger().Log(L"==========================");
		GM::GetLogger().Log(L"[Space bar] 게임 시작");
		break;

	case GameState::CREATE_CHARACTER:
		GM::GetLogger().Log(L"캐릭터를 생성합니다.");
		GM::GetLogger().Log(L"[ENTER] 진행");
		break;

	case GameState::STORY:
		GM::GetLogger().Log(L"스토리를 진행합니다.");
		GM::GetLogger().Log(L"[B] 전투 | [S] 상점 | [I] 상태창");
		break;

	case GameState::SHOP:
		GM::GetLogger().Log(L"상점에 진입했습니다.");
		GM::GetLogger().Log(L"[ESC] 나가기");
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
}

// ==========================================================
// 각 상태별 로직
// ==========================================================

void TextRPG::UpdateTitle()
{
	if (GM::GetInput().IsKeyDown(VK_SPACE))
	{
		ChangeState(GameState::CREATE_CHARACTER);
	}
}

void TextRPG::UpdateCreateCharacter()
{
	// 이름 입력 로직

	if (GM::GetInput().IsKeyDown(VK_RETURN))
	{
		if (player == nullptr)
		{
			player = GM::CreateActor<Character>(L"유진");
			player->Init();
		}
		GM::GetLogger().Log(L"캐릭터 생성 완료!");
		ChangeState(GameState::STORY);
	}
}

void TextRPG::UpdateStory()
{
	if (GM::GetInput().IsKeyDown('B'))
	{
		// 레벨 10 이상이면 보스전

		currentMonster = GM::CreateActor<Monster>(L"몬스터");
		currentMonster->Init(player->getLevel());
		battleManager = GM::CreateActor<BattleManager>(L"BattleManager");
		battleManager->StartBattle(player, currentMonster);

		ChangeState(GameState::BATTLE);
	}
	else if (GM::GetInput().IsKeyDown('S'))
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

	GM::DestroyActor(battleManager);
	battleManager = nullptr;

	GM::DestroyActor(currentMonster);
	currentMonster = nullptr;

	ChangeState(GameState::STORY);

}

void TextRPG::UpdateShop()
{
	// 상점 로직
	if (GM::GetInput().IsKeyDown(VK_ESCAPE))
	{
		ChangeState(GameState::STORY);
	}
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

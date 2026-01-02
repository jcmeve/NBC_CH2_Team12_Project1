#include <Windows.h>
#include "TextRPG.h"
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "BattleManager.h"
#include<string>
#include "Widget.h"
#include "QTE.h"
 //   QTE* qte = GM::CreateActor<QTE>(L"QTE TEST");
 //   qte->Init(nullptr, 3);
TextRPG::TextRPG(std::wstring name) : Actor(name) {}

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
	case GameState::BOSS_BATTLE:
		//일반 전투랑 로직이 같으니까 BATTLE 안에 넣어도?
		break;
	case GameState::ENDING:
		UpdateEnding();
		break;
	default:
		break;
	}

}

void TextRPG::UpdateTitle()
{
	// 타이틀 UI 추가
	// GM::GetDisplay().DrawWidget(30, 10, 40, 10, L"Text RPG", L" Press Space to Start");
	if (isKeyJustPressed(VK_SPACE))
	{
		GM::GetLogger().Log(L"게임을 시작합니다!!!");
		ChangeState(GameState::CREATE_CHARACTER);
	}
}

void TextRPG::UpdateCreateCharacter()
{
	if (player == nullptr)
	{
		// 이름 입력 추가
		player = GM::CreateActor<Character>(L"유진");
		player->Init();

		GM::GetLogger().Log(L"캐릭터 생성 완료! 스토리를 진행합니다.");
		ChangeState(GameState::STORY);
	}
}

void TextRPG::UpdateStory()
{
	// B키 입력으로 전투 시작
	if (isKeyJustPressed('B'))
	{
		// 레벨 10 이상이면 보스전

		Monster* monster = GM::CreateActor<Monster>(L"몬스터");
		monster->Init(player->getLevel());

		battleManager = GM::CreateActor<BattleManager>(L"BattleManager");
		battleManager->StartBattle(player, monster);

		ChangeState(GameState::BATTLE);
	}
}

void TextRPG::UpdateBattle()
{
	if (battleManager == nullptr)
	{
		ChangeState(GameState::STORY);
		return;
	}

	if (battleManager->GetBattleState() == BattleState::BS_END)
	{
		GM::DestroyActor(battleManager);
		battleManager = nullptr;
		ChangeState(GameState::STORY);
	}
}

void TextRPG::UpdateShop()
{
	// 상점 로직
}

void TextRPG::UpdateEnding()
{
	// 엔딩 크레딧 & 게임 종료 처리
}

void TextRPG::ChangeState(GameState newState)
{
	currentState = newState;
	GM::GetDisplay().ClearTextArea();

	// 상태 변경 시 초기화 로직이 필요하다면 추가할것
}

bool TextRPG::isKeyJustPressed(int key)
{
	bool isPressed = (GetAsyncKeyState(key) & 0x8000) != 0;

	if (keyState.find(key) == keyState.end())
	{
		keyState[key] = false;
	}

	bool wasPressed = keyState[key];
	keyState[key] = isPressed;

	return isPressed && !wasPressed;
}

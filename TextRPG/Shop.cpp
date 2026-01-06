#include "Shop.h"
#include "VectorWidget.h"
#include "GameManager.h"
#include "UsableItem.h"
#include "Equipment.h"
#include "Artifact.h"
#include "Character.h"
#include "Inventory.h"

void Shop::Enter(Character* _player) {
    widget = GM::CreateActor<VectorWidget>();
    player = _player;
    mode = MODE::BUY;
    idx = 0;
    ReloadItems();

    
    manualWidget = GM::CreateActor<Widget>(L"조작법");
    manualWidget->Init(150, 40, 30, 5);
    manualWidget->SetText(L"[ESC] : 나가기\n[◀ ▶] : 구매/판매 전환\n[▲ ▼] : 이동\n[ENTER] : 거래하기");
    GM::GetDisplay().ClearTextArea();
    GM::GetLogger().Log(L"=============== 상점에 진입했습니다 ===============");

}

void Shop::Tick(float deltatTime) {
    if (GM::GetInput().IsKeyDown(VK_LEFT) || GM::GetInput().IsKeyDown(VK_RIGHT)) {
        SwitchWidget();
        return;
    }

    if (GM::GetInput().IsKeyDown(VK_DOWN)) {
        IdxUpdate(idx + 1);
        return;
    }
    else if (GM::GetInput().IsKeyDown(VK_UP)) {
        IdxUpdate(idx - 1);
        return;
    }

    if (GM::GetInput().IsKeyDown(VK_RETURN)) {
        Trade();
    }

}
void Shop::Trade() {
    std::wstring resultText;
    if (mode == MODE::BUY) {
        const Item* item = GM::GetItemManager().GetAllItems()[idx];
        int price = item->GetPrice();
        int gold = player->getGold();
        if (gold < price) {
            GM::GetLogger().Log(L"소지금이 부족합니다!");
            return;
        }
        player->RemoveGold(price);
        player->getInventory()->AddItem(item);
        resultText = item->GetName() + L" 구매 성공!  남은 골드 : " + std::to_wstring(player->getGold());
        GM::GetSound().PlayAudio(L"Buy_Coin");
    }
    else if (mode == MODE::SELL) {
        const auto* pair = player->getInventory()->GetItem(idx);
        if (!pair) {
            GM::GetLogger().Log(L"아이템을 팔 수 없었습니다..");
            return;
        }
        auto itemName = pair->first->GetName();
        int price = pair->first->GetPrice();
        player->getInventory()->RemoveItem(pair->first);
        player->addGold(price);
        resultText =itemName + L" 판매 성공!  남은 골드 : " + std::to_wstring(player->getGold());
        GM::GetSound().PlayAudio(L"Sell_Coin");
    }
    ReloadItems();
    IdxUpdate(idx);
    GM::GetLogger().Log(resultText);
}
void Shop::IdxUpdate(int _idx) {
    int size = widget->GetLineCount();
    if (size == 0)return;
    idx = (_idx + size) % size;
    widget->SetHighlight(idx);
    GM::GetDisplay().ClearTextArea();
    const Item* item = nullptr;
    if (mode == MODE::BUY) {
        item = GM::GetItemManager().GetAllItems()[idx];
    }
    else if (mode == MODE::SELL) {
        item = player->getInventory()->GetItem(idx)->first;
    }

    std::wstring resultText = item->GetDesc();

    int hp = 0, dmg = 0, def = 0;
    for (const auto& pair : item->GetEffects()) {
        switch (pair.first)
        {
        case STATS::HP:hp = pair.second; break;
        case STATS::ATK:dmg = pair.second; break;
        case STATS::DEF:def = pair.second; break;
        default:
            break;
        }
    }
    if (hp) {
        if (dynamic_cast<const UsableItem*>(item)) {
            resultText += L" HP 회복 : " + std::to_wstring(hp);
        }
        else {
            resultText += L" 최대 HP 증가 : " + std::to_wstring(hp);
        }
    }
    if (dmg) resultText += L" 공격력 증가 : " + std::to_wstring(dmg);
    if (def) resultText += L" 방어력 증가 : " + std::to_wstring(def);
    if (const UsableItem* usable = dynamic_cast<const UsableItem*>(item)) {
        resultText += L" 지속시간 : " + std::to_wstring(usable->GetDuration());
        resultText += L" 소모품";
    }
    else if (dynamic_cast<const Equipment*>(item)) {
        resultText += L" 장비";
    }
    else if (dynamic_cast<const Artifact*>(item)) {
        resultText += L" 아티팩트";
    }

    GM::GetLogger().Log(resultText);

}
void Shop::Exit() {
    GM::DestroyActor(widget);
    GM::DestroyActor(manualWidget);
    player = nullptr;
}


void Shop::SwitchWidget() {
    if (mode == MODE::BUY)
        mode = MODE::SELL;
    else if (mode == MODE::SELL)
        mode = MODE::BUY;
    idx = 0;
    ReloadItems();
}

void Shop::ReloadItems() {
    if (mode == MODE::BUY) {
        widget->Init(10, 5, 80, 50);
        auto ret = GM::GetItemManager().GetAllItems();
        std::vector<std::wstring> texts;
        for (auto& item : ret) {
            texts.push_back(item->GetName() + L" : " + std::to_wstring(item->GetPrice())+L"G");
        }
        widget->SetTexts(texts);
        widget->SetName(L"구매하기");

    }
    else if (mode == MODE::SELL) {
        widget->Init(10, 5, 80, 50);
        std::vector<std::wstring> texts;

        int i = 0;
        while (const auto& pair = player->getInventory()->GetItem(i)) {
            ++i;
            texts.push_back(pair->first->GetName() + L" : " + std::to_wstring((int)(pair->first->GetPrice() * 0.6)) + L"G   " + std::to_wstring(pair->second) + L"개");
        }

        widget->SetTexts(texts);
        widget->SetName(L"판매하기");
    }
}

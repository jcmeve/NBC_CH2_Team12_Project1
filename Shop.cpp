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
        GM::GetLogger().Log(item->GetName() + L" 구매 성공!  남은 골드 : " + std::to_wstring(player->getGold()));
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
        GM::GetLogger().Log(itemName + L" 판매 성공!  남은 골드 : " + std::to_wstring(player->getGold()));
    }
    ReloadItems();
    IdxUpdate(idx);
}
void Shop::IdxUpdate(int _idx) {
    int size = widget->GetLineCount();
    if (size == 0)return;
    int originIdx = idx;
    idx = (_idx + size) % size;
    widget->SetHighlight(idx);

}
void Shop::Exit() {
    GM::DestroyActor(widget);
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
            texts.push_back(item->GetName() + L" : " + std::to_wstring(item->GetPrice()));
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
            texts.push_back(pair->first->GetName() + L" : " + std::to_wstring((int)(pair->first->GetPrice() * 0.6)) + L"   " + std::to_wstring(pair->second) + L"개");
        }

        widget->SetTexts(texts);
        widget->SetName(L"판매하기");
    }
}

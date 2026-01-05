#include "Shop.h"
#include "VectorWidget.h"
#include "GameManager.h"
#include "Item.h"
#include "Character.h"
#include "Inventory.h"

void Shop::Enter(Character* _player) {
    widget = GM::CreateActor<VectorWidget>();
    player = _player;
    mode = MODE::SELL;
    idx = 0;
}

void Shop::Tick(float deltatTime) {
    if (GM::GetInput().IsKeyDown(VK_LEFT) || GM::GetInput().IsKeyDown(VK_RIGHT)) {
        SwitchWidget();
    }
    if (GM::GetInput().IsKeyDown(VK_DOWN)) {
        IdxUpdate(idx + 1);
    }
    else if (GM::GetInput().IsKeyDown(VK_UP)) {
        IdxUpdate(idx - 1);
    }

}
void Shop::IdxUpdate(int _idx) {
    int size = widget->GetLineCount();
    if (size == 0)return;
    int originIdx = idx;
    idx = (_idx + size) % size;
    if (originIdx == idx) return;
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
        auto ret = player->getInventory()->GetAllItems();
        std::vector<std::wstring> texts;

        for (auto& item : ret) {
            texts.push_back(item.first->GetName() + L" : " + std::to_wstring(item.first->GetPrice()) + L"\t" + std::to_wstring(item.second));
        }
        widget->SetTexts(texts);
        widget->SetName(L"판매하기");
    }


}

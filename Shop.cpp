#include "Shop.h"
#include "Widget.h"
#include "GameManager.h"
#include "Item.h"
#include "Character.h"
#include "Inventory.h"

void Shop::Enter(Character* _player) {
    widget = GM::CreateActor<Widget>();
    player = _player;
    mode = MODE::SELL;
}

void Shop::Tick(float deltatTime) {
    if (GM::GetInput().IsKeyDown(VK_LEFT) || GM::GetInput().IsKeyDown(VK_RIGHT)) {
        
    }
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

    if (mode == MODE::BUY) {
        mode = MODE::SELL;
        widget->Init(0, 0, 40, 50);
        auto ret = GM::GetItemManager().GetAllItems();

        std::wstring text;
        for (auto& item : ret) {
            text += item->GetName() + L" : " + std::to_wstring(item->GetPrice()) + L"\n";
        }
        widget->SetText(text);
    
    }
    else if (mode == MODE::SELL) {
        mode = MODE::BUY;
        widget->Init(0, 0, 40, 50);
        auto ret = player->getInventory()->GetAllItems();

        std::wstring text;
        for (auto& item : ret) {
            text += item.first->GetName() + L" : " + std::to_wstring(item.first->GetPrice()) + L"\t" + std::to_wstring(item.second) + L"\n";
        }
        widget->SetText(text);
    }


}

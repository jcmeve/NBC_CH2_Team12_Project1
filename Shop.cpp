#include "Shop.h"
#include "Widget.h"
#include "GameManager.h"
void Shop::Enter(Character* _player) {
    widget = GM::CreateActor<Widget>();
    mode = MODE::BUY;
}

void Shop::Tick(float deltatTime) {
    if (GM::GetInput().IsKeyDown(VK_LEFT) || GM::GetInput().IsKeyDown(VK_RIGHT)) {
        
    }
    

}

void Shop::SwitchWidget() {
    //if (mode == MODE::BUY) {
    //    mode = MODE::SELL;
    //    widget->Init(0, 0, 40, 50);
    //    auto ret = GM::GetItemManager().GetAllItems();
    //    std::wstring text;
    //    for (auto item : ret) {
    //        text += item+L"\n";
    //    }
    //    widget->SetText(text);
    //
    //}
    //else if (mode == MODE::SELL) {
    //    mode = MODE::BUY;
    //}


}

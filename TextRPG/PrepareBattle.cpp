#include "PrepareBattle.h"
#include "VectorWidget.h"
#include "GameManager.h"
#include "Character.h"
#include "Inventory.h"
void PrepareBattle::Enter(Character* _player) {
    EquipmentsWidget = GM::CreateActor<VectorWidget>();
    InventoryEquipmentsWidget = GM::CreateActor<VectorWidget>();
    player = _player;
    mode = MODE::EQUIP;
    idx = 0;
    ReloadItems();

    manualWidget = GM::CreateActor<Widget>(L"조작법");
    manualWidget->Init(150, 40, 30, 5);
    manualWidget->SetText(L"[ESC] : 나가기\n[◀ ▶] : 장비/인벤토리 전환\n[▲ ▼] : 이동\n[ENTER] : 장비 교체");
    GM::GetDisplay().ClearTextArea();
    GM::GetLogger().Log(L"=============== 전투중비에 돌입했습니다 ===============");
}

void PrepareBattle::Tick(float deltatTime) {
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
        TryEquip();
    }

}



void PrepareBattle::TryEquip() {
    std::wstring resultText;
    if (mode == MODE::EQUIP) {
        const Equipment* item = (*std::next(player->getInventory()->GetEquipments().begin(), idx)).first;
        if (!item) {
            GM::GetLogger().ErrorLog(L"TryEquip");
        }
        if (!player->Equip(item)) {
            GM::GetLogger().Log(L"장비칸이 가득 찼습니다!");
            return;
        }
        resultText = item->GetName() + L" 장착 성공!";
    }
    else if (mode == MODE::UNEQUIP) {
        const Equipment* item = player->GetCurrentEquipment(idx);
        if (!item) {
            return;
        }
        player->Unequip(idx);

        auto itemName = item->GetName();
        resultText = itemName + L" 탈착 성공!" ;
    }
    ReloadItems();
    IdxUpdate(idx);
    GM::GetLogger().Log(resultText);
}



void PrepareBattle::IdxUpdate(int _idx) {
    if (mode == MODE::EQUIP) {
        int size = player->getInventory()->GetEquipments().size();
        if (size == 0)return;
        idx = (_idx + size) % size;
        InventoryEquipmentsWidget->SetHighlight(idx);
        EquipmentsWidget->SetHighlight(-1);

    }
    else if (mode == MODE::UNEQUIP) {
        int size = player->GetCurrentEquipmentSize();
        if (size == 0)return;
        idx = (_idx + size) % size;
        EquipmentsWidget->SetHighlight(idx);
        InventoryEquipmentsWidget->SetHighlight(-1);
    }

    GM::GetDisplay().ClearTextArea();
    const Equipment* item = nullptr;



    if (mode == MODE::EQUIP) {
        item = (*std::next(player->getInventory()->GetEquipments().begin(), idx)).first;
    }
    else if (mode == MODE::UNEQUIP) {
        item = player->GetCurrentEquipment(idx);
    }
    if (!item) {
        return;
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

    if (hp)  resultText += L" 최대 HP 증가 : " + std::to_wstring(hp);
    if (dmg) resultText += L" 공격력 증가 : " + std::to_wstring(dmg);
    if (def) resultText += L" 방어력 증가 : " + std::to_wstring(def);

    GM::GetLogger().Log(resultText);

    if (mode == MODE::EQUIP) {
        InventoryEquipmentsWidget->SetHighlight(idx);
        EquipmentsWidget->SetHighlight(-1);
    }
    else if (mode == MODE::UNEQUIP) {
        EquipmentsWidget->SetHighlight(idx);
        InventoryEquipmentsWidget->SetHighlight(-1);
    }


}


void PrepareBattle::Exit() {
    GM::DestroyActor(EquipmentsWidget);
    GM::DestroyActor(InventoryEquipmentsWidget);
    GM::DestroyActor(manualWidget);
    player = nullptr;
}


void PrepareBattle::SwitchWidget() {
    if (mode == MODE::EQUIP)
        mode = MODE::UNEQUIP;
    else if (mode == MODE::UNEQUIP)
        mode = MODE::EQUIP;
    idx = 0;
    ReloadItems();
}

void PrepareBattle::ReloadItems() {

    {
        EquipmentsWidget->Init(10, 5, 80, 50);
        auto ret = GM::GetItemManager().GetAllItems();
        std::vector<std::wstring> texts;

        for (int i = 0; i < player->GetCurrentEquipmentSize(); ++i) {
            const Equipment* item = player->GetCurrentEquipment(i);
            if (item) {
                texts.push_back(item->GetName() + L" : " + std::to_wstring(item->GetPrice()) + L"G");
            }
            else {
                texts.push_back(L" ");

            }
        }
        EquipmentsWidget->SetTexts(texts);
        EquipmentsWidget->SetName(L"장착중인 장비");
    }
    
    {
        InventoryEquipmentsWidget->Init(100, 5, 80, 50);
        std::vector<std::wstring> texts;

        int i = 0;

        const auto& map = player->getInventory()->GetEquipments();
        for (const auto& pair : map) {
            texts.push_back(pair.first->GetName() + L" : " + std::to_wstring((int)(pair.first->GetPrice() * 0.6)) + L"G   " + std::to_wstring(pair.second) + L"개");
        }
        
        InventoryEquipmentsWidget->SetTexts(texts);
        InventoryEquipmentsWidget->SetName(L"소유중인 장비");
    }


    if (mode == MODE::EQUIP) {
        InventoryEquipmentsWidget->SetHighlight(idx);
        EquipmentsWidget->SetHighlight(-1);
    }
    else if (mode == MODE::UNEQUIP) {
        EquipmentsWidget->SetHighlight(idx);
        InventoryEquipmentsWidget->SetHighlight(-1);
    }
}

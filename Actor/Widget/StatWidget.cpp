#include "StatWidget.h"
#include "Pawn.h"
void StatWidget::Tick(float deltaTime) {
    std::wstring resultText;
    resultText += L"체력 " + std::to_wstring(target->GetHealth()) + L"/" + std::to_wstring(target->GetMaxHealth()) + L"\n";
    resultText += L"공격력 " + std::to_wstring(target->GetOriginDamage()) + L"+" + std::to_wstring(target->GetDamage() - target->GetOriginDamage()) + L"\n";
    resultText += L"방어력 " + std::to_wstring(target->GetOriginDefence()) + L"+" + std::to_wstring(target->GetDefence() - target->GetOriginDefence()) + L"\n";
    SetText(resultText);
    Widget::Tick(deltaTime);
}

void StatWidget::SetTarget(const Pawn* pawn) {
    target = pawn;
}

StatWidget::StatWidget(std::wstring name) :Widget(name) {
}

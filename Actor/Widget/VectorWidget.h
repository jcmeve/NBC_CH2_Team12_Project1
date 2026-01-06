#pragma once
#include "Widget.h"
#include <vector>
#include <string>
class VectorWidget : public Widget {
private:
    std::vector<std::wstring> texts;
    int highlightIdx = 0;
public:
    VectorWidget(std::wstring _name);
    void SetTexts(const std::vector<std::wstring>& _texts);
    void SetHighlight(int idx);
    int GetLineCount()const;
};


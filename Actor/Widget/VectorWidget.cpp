#include "VectorWidget.h"

VectorWidget::VectorWidget(std::wstring _name) :Widget(_name) {
    
}

void VectorWidget::SetTexts(const std::vector<std::wstring>& _texts) {
    texts.assign(_texts.begin(),_texts.end());
    SetHighlight(-1);
}

void VectorWidget::SetHighlight(int idx) {
    highlightIdx = idx;
    std::wstring str;
    for (int i = 0; i < texts.size(); ++i) {
        if (i == highlightIdx) {
            str += L'█';
        }
        str += texts[i] + L'\n';
    }
    SetText(str);
}

int VectorWidget::GetLineCount() const {
    return texts.size();
}



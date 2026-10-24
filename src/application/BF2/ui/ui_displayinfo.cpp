#include "mm/Col4.h"
#include "classes/ui/UIColorLibrary.h"
#include "classes/ui/UIDisplayInfo.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/Hash.h"
#include "ui/UIUtil.h"

namespace ui {

UIDisplayInfo::UIDisplayInfo()
    : m_disp(true), m_center(0), m_blendType(0), m_priority(0), m_mulColor(1.0f, 1.0f, 1.0f, 1.0f),
      m_addColor(0.0f, 0.0f, 0.0f), m_pixelWidth(0), m_pixelHeight(0), m_changed(false), m_defColor(nullptr),
      m_linkColor(nullptr) {}

void UIDisplayInfo::saveDefColor() {
    if (m_defColor == nullptr) {
#line 130
        m_defColor = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) DefColor();
    }
    m_defColor->m_addColor = getColorInfo()->m_addColor;
    m_defColor->m_mulColor = mm::Col3(getColorInfo()->m_mulColor.r, getColorInfo()->m_mulColor.g,
                                      getColorInfo()->m_mulColor.b);
}

UIDisplayInfo::~UIDisplayInfo() {
    if (m_defColor != nullptr) {
        delete m_defColor;
        m_defColor = nullptr;
    }
}

void UIDisplayInfo::syncParent() {}

void UIDisplayInfo::setDisp(bool disp) {
    if (m_disp != disp) {
        m_changed = true;
    }
    m_disp = disp;
}

void UIDisplayInfo::loadDefColor() {
    if (m_defColor != nullptr) {
        m_addColor = m_defColor->m_addColor;
        m_mulColor = mm::Col4(m_defColor->m_mulColor.r, m_defColor->m_mulColor.g, m_defColor->m_mulColor.b,
                              getColorInfo()->m_mulColor.a);
    }
}

void UIDisplayInfo::linkColor(const UIDisplayInfo* info) {
    m_linkColor = info;
}

void UIDisplayInfo::setPixelWidth(unsigned short width) {
    if (m_pixelWidth != width) {
        m_changed = true;
    }
    m_pixelWidth = width;
}

void UIDisplayInfo::setPixelHeight(unsigned short height) {
    if (m_pixelHeight != height) {
        m_changed = true;
    }
    m_pixelHeight = height;
}

void UIDisplayInfo::operator=(const UIDisplayInfo& other) {
    m_disp = other.m_disp;
    m_center = other.m_center;
    m_priority = other.m_priority;
    m_mulColor = other.m_mulColor;
    m_addColor = other.m_addColor;
    m_pixelWidth = other.m_pixelWidth;
    m_pixelHeight = other.m_pixelHeight;
    m_changed = true;
    if (other.m_defColor != nullptr) {
        saveDefColor();
    }
}

}  // namespace ui

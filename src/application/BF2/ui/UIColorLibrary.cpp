#include "mm/Col4.h"
#include "classes/ui/UIColorLibrary.h"
#include "classes/ui/UIDisplayInfo.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/Hash.h"
#include "ui/UIUtil.h"

namespace ui {

UIColorLibrary::UIColorLibrary() {
    m_colors.setAllocator(UIUtil::getProgAllocator());
    m_colors.reserve(8, 8);
}

UIColorLibrary::~UIColorLibrary() {
    reset();
}

bool UIColorLibrary::add(const char* name, const mm::Col4& color) {
    unsigned int hash = mm::mtl::hashStrCrc(name);
    for (ColorInfo* it = m_colors.begin(); it != m_colors.end(); ++it) {
        if (it->m_hash == hash) {
            it->m_color = color;
            return true;
        }
    }
    ColorInfo info;
    info.m_hash = hash;
    info.m_color = color;
    m_colors.push_back(info);
    return true;
}

bool UIColorLibrary::find(const char* name, mm::Col4& color) {
    unsigned int hash = mm::mtl::hashStrCrc(name);
    color = mm::Col4::white;
    for (ColorInfo* it = m_colors.begin(); it != m_colors.end(); ++it) {
        if (it->m_hash == hash) {
            color = it->m_color;
            return true;
        }
    }
    return false;
}

}  // namespace ui

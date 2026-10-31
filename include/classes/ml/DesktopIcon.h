#ifndef CLASSES_ML_DESKTOPICON_H
#define CLASSES_ML_DESKTOPICON_H

#include "classes/ml/DevGraph.h"
#include "mm/Rect.h"
#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"

namespace ml {
// table 0x7100B786B8; 0x70 bytes (create allocates it so)
class DesktopIcon {
public:
    // an icon named name that runs func, 0x70 bytes from mem (the parameter names are not the original's)
    static DesktopIcon* create(mtl::ALLOC_HANDLE mem, const char* name, void (*func)());
    // inline: create inlines it (the parameter names are not the original's)
    DesktopIcon(const char* name, void (*func)()) : m_name(name), m_func(func), m_select(false) {
        m_rect = mm::Rect<int>(0, 0, DevGraph::fontGetWidth(name, FONT_STYLE(0), 1.0f), 25);
    }
    virtual ~DesktopIcon() {}  // slot 0
    // the field names are not the original's
    mm::mtl::FixStr<64> m_name;  // 0x08
    void (*m_func)();            // 0x50
    mm::Rect<int> m_rect;        // 0x58 0, 0, the name's width, 25
    bool m_select;               // 0x68
};
}  // namespace ml

#endif

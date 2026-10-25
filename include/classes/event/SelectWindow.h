#ifndef CLASSES_EVENT_SELECTWINDOW_H
#define CLASSES_EVENT_SELECTWINDOW_H

#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjBalloon.h"

namespace event {
// table 0x7100B3D728
class SelectWindow {
public:
    virtual ~SelectWindow() {}  // slot 0
    // out of line (SelectManager::OnEventProc branches to it)
    void update();
    // 1.0.0's SelectWindow::clear (0x71000F59C8); 3.0.1 inlines it: closes the balloon and lets its context go
    void clear() {
        if (m_context != nullptr) {
            gf::GfMenuObjBalloon::close(m_context, true);
            if (m_context != nullptr) {
                m_context->release();
                m_context = nullptr;
            }
        }
        pad_8 = 0;
    }
    unsigned int pad_8;
    unsigned int pad_c;
    gf::GfMenuCallContext* m_context;  // 0x10 the balloon's call context (the name is not the original's)
    unsigned char pad_18[0x8];
};
}  // namespace event

#endif

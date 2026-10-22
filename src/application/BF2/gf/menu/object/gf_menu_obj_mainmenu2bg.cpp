#include "ui/EventData.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/gf/GfMenuObjMainMenu2BG.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

GfMenuObjMainMenu2BG::GfMenuObjMainMenu2BG(unsigned int handle)
    : GfMenuObject(handle), m_resultHandle(0), m_list(nullptr), m_bgList(nullptr) {}

GfMenuObjMainMenu2BG::~GfMenuObjMainMenu2BG() {
    if (m_bgList != nullptr) {
        m_bgList->release();
        m_bgList = nullptr;
    }
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

// initialize (0x7100433D04) is not here yet: see the report

void GfMenuObjMainMenu2BG::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMainMenu2BG::update() {
    if (m_bgList != nullptr) {
        for (unsigned int i = 0; i < m_bgList->getSize(); i++) {
            ui::UIObjectAcc bg(m_bgList->getObject(i));
            if (!bg.isStreaming()) {
                bg.setAlpha(1.0f);
                bg.startAnimationFromIndex(1, false);
                m_bgList->delObject(bg.m_handle);
            }
        }
    }
    GfMenuObject::update();
}

// MainListener::reciveEvent (0x7100434374) is not here yet: see the report

void GfMenuObjMainMenu2BG::move(GfMenuCallContext* context, unsigned int handle, const OpenMainMenuBg& param) {
    unsigned int bg = GfMenuObject::getAttachedObject(0x60);
    if (ui::UIObjectAcc(bg).m_object != nullptr) {
        if (!ui::UIObjectAcc(bg).isTerm()) {
            ui::EventData event;
            event.m_type = 0x101;
            event.m_param0 = param.m_move;
            event.m_param1Float = param.m_time;
            event.m_param2 = param.m_count;
            event.m_param3 = handle;
            ui::UIManager::get()->requestObjectEvent(bg, event, 0.0f);
        }
    }
}

}  // namespace gf

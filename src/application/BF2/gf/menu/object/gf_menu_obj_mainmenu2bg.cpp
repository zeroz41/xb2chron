#include "ui/EventData.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/gf/GfMenuObjMainMenu2BG.h"
#include "classes/gf/GfMenuObjMainMenu2BG/MainListener.h"
#include "classes/gf/GfInfo.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Rect.h"
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

// initialize (0x7100433D04) is not here yet

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

void GfMenuObjMainMenu2BG::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        acc.setDisp(false);
        break;
    case 3:
        if (event.m_param0 == 1 && m_owner->m_resultHandle != 0) {
            GfMenuObject::addResultCallContext(m_owner->m_resultHandle, 1, 0);
            m_owner->m_resultHandle = 0;
        }
        break;
    case 0x101: {
        short screenW = GfScreenW();
        unsigned int count = event.m_param2;
        int move = event.m_param0;
        m_owner->m_resultHandle = event.m_param3;
        for (unsigned int i = 0; i < m_owner->m_list->getSize(); i++) {
            mm::Rect<short> rect;
            ui::UIObjectAcc bg(m_owner->m_list->getObject(i));
            bg.getRect(rect, 2);
            unsigned int step = (rect.w - screenW) / (count - 1);
            int dist = step * move;
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x80;
            param.m_curve = 1;
            param.m_time = event.m_param1Float;
            param.m_pos.x = -dist;
            param.m_eventId = 1;
            param.m_pos.y = 0;
            if (GfMenuObjUtil::isValidExpansion(3)) {
                if (m_owner->m_positions[i].m_flip == 1) {
                    param.m_pos.x = m_owner->m_positions[i].m_x + dist;
                } else {
                    param.m_pos.x = m_owner->m_positions[i].m_x - dist;
                }
            }
            int ctrl = GfMenuObjUtil::startCtrl(bg.m_handle, param, nullptr);
            if (i == 0) {
                GfMenuObject::hookCtrlEvent(handle, ctrl);
            }
        }
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

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

#include "ui/EventData.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuObjMainSubmenu.h"
#include "classes/gf/GfMenuObjMainSubmenu/ListListener.h"
#include "classes/gf/GfMenuObjMainSubmenu/MainListener.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/ui/UISelectObjList.h"

namespace gf {

GfMenuObjMainSubmenu::GfMenuObjMainSubmenu(unsigned int handle)
    : GfMenuObject(handle), m_kind(0), m_guideText(0), m_subIndexText(0), m_list(nullptr), m_items(),
      m_fadeOnClose(true), m_context(nullptr) {
    for (int i = 0; i < 5; i++) {
        m_growCtrl[i] = -1;
    }
}

GfMenuObjMainSubmenu::~GfMenuObjMainSubmenu() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void GfMenuObjMainSubmenu::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMainSubmenu::update() {
    GfMenuObject::update();
}

void GfMenuObjMainSubmenu::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::sendEvent(acc.m_handle, ui::EventData(0x21), 0.0f);
        break;
    case 2: {
        ui::EventData open(0x22);
        open.m_param0 = 1;
        GfMenuObject::sendEvent(acc.m_handle, open, 0.0f);
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObjMainMenu2::setSystemKeyEnable(true);
            GfMenuObjMainMenu2::setCloseKeyEnable(true);
            GfMenuObject::enableInput(acc.searchChild("LAY_item_list"));
            GfMenuObjOperationInfo::add(acc.searchChild("LAY_item_list"), 0, 0, 0);
        } else if (event.m_param0 == 2) {
            acc.setTerm();
        }
        break;
    case 0x21: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 0x22: {
        if (m_owner->m_fadeOnClose) {
            bool keep = event.m_param0 == 1;
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_out = 1;
            param.m_preset = 6;
            param.m_eventId = 2;
            param.m_startFlag1 = keep;
            GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        } else {
            ui::EventData term(3);
            term.m_param0 = 2;
            ui::UIManager::get()->requestObjectEvent(handle, term, 0.0f);
        }
        ui::EventData close;
        close.m_type = 0x22;
        GfMenuObject::sendEvent(acc.searchChild("LAY_item_list"), close, 0.0f);
        break;
    }
    case 0x24: {
        GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        m_owner->m_fadeOnClose = false;
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf

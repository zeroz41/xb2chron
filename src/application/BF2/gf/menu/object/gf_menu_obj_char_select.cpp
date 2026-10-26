#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjCharSelect/MainListener.h"
#include "classes/gf/GfMenuObjCharSelect/CharListener.h"
#include "classes/gf/GfMenuObjCharSelect/SubMenuListener.h"
#include "classes/gf/GfMenuObjCharSelect/DetailListener.h"
#include "classes/gf/GfMenuObjCharSelect/StatusListener.h"
#include "classes/gf/GfMenuObjCharSelect/CharDrListener.h"
#include "classes/gf/GfMenuObjCharSelect/CharBlMoveListener.h"
#include "classes/gf/GfMenuObjCharSelect/CharDrMoveListener.h"
#include "classes/gf/GfMenuObjCharSelect/CharDrSoloListener.h"
#include "ui/EventData.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/SCOM_NIA_BLADE.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfMenuManager.h"

namespace gf {

namespace {
// an event of that type with that first parameter, requested of the handle's object at once (inline: its event sits
// above the callers' locals; the name is not the original's)
inline void requestEvent(unsigned int handle, unsigned short type, int param) {
    ui::EventData event;
    event.m_type = type;
    event.m_param0 = param;
    ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}
}  // namespace

GfMenuObjCharSelect::~GfMenuObjCharSelect() {
    if (m_subContext != nullptr) {
        m_subContext->release();
        m_subContext = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    if (m_unusedList != nullptr) {
        m_unusedList->release();
        m_unusedList = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        if (m_bladeLists[i] != nullptr) {
            m_bladeLists[i]->release();
            m_bladeLists[i] = nullptr;
        }
    }
}

void GfMenuObjCharSelect::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjCharSelect::update() {
    m_seq.update();
    GfMenuObject::update();
}

bool GfMenuObjCharSelect::seqStreamWaitStatDrBefore() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc move(acc.searchChild("LAY_char_dr_move"));
    int ctrl = GfMenuObjUtil::getCtrlID(move.m_handle);
    if (ctrl != -1) {
        GfMenuObjUtil::stopCtrl(ctrl);
    }
    return true;
}

bool GfMenuObjCharSelect::seqStreamWaitStatBlBefore() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc move(acc.searchChild("LAY_char_bl_move"));
    int ctrl = GfMenuObjUtil::getCtrlID(move.m_handle);
    if (ctrl != -1) {
        GfMenuObjUtil::stopCtrl(ctrl);
    }
    return true;
}

bool GfMenuObjCharSelect::seqConfSpecialWaitError() {
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    m_seq.addJob(&GfMenuObjCharSelect::seqReturn);
    pad_6C0 = false;
    return true;
}

bool GfMenuObjCharSelect::seqSpHomuraToHikari() {
    GfGameUtil::changeHikariCurrent(true);
    return true;
}

bool GfMenuObjCharSelect::seqSpHikariToHomura() {
    GfGameUtil::changeHikariCurrent(false);
    return true;
}

bool GfMenuObjCharSelect::seqSpNiaChangeDr() {
    SCOM_NIA_BLADE::create(false);
    return true;
}

bool GfMenuObjCharSelect::seqReturn() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    requestEvent(acc.m_handle, 0x107, 0);
    return true;
}

bool GfMenuObjCharSelect::seqReturnChange() {
    ui::UIObjectAcc acc(m_handle, "LAY_char");
    requestEvent(acc.m_handle, 0x107, 1);
    return true;
}

void GfMenuObjCharSelect::returnSubMenu() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x61);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x104;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjCharSelect::execCharPosScale(unsigned int param) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x61);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            requestEvent(handle, 0x109, param);
        }
    }
}

bool GfMenuObjCharSelect::attach(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x61));
    if (acc.m_object != nullptr) {
        GfMenuObject::startCallContext(context, 0x61, acc.m_handle);
        return true;
    }
    return false;
}

}  // namespace gf

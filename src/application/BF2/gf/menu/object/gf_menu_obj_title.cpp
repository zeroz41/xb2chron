#include "classes/tl/TitleMain.h"
#include "classes/gf/GfMenuObjTitle.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuMsgList.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "ui/UIUtil.h"

namespace gf {

namespace {
// Proposed names, not the original's: the symbols leave the table unnamed (lbl_7100B64D80, file-local: initialize
// and moveCursor reach it by adrp+add). The title menu's items: the layout pane each item shows in and the test that
// shows it.
struct TitleItem {
    const char* m_name;
    bool (*m_isEnable)();
};
TitleItem s_titleItems[5] = {
    {"TXT_newgame", GfMenuObjTitle::isEnableNewGame},
    {"TXT_continue", GfMenuObjTitle::isEnableContinue},
    {"TXT_option", GfMenuObjTitle::isEnableOption},
    {"TXT_theater", GfMenuObjTitle::isEnableEventsTheater},
    {"TXT_newgame_adv", GfMenuObjTitle::isEnableNewGameAdv},
};
}  // namespace

bool GfMenuObjTitle::s_NoSaveData = true;

GfMenuObjTitle::GfMenuObjTitle(unsigned int handle)
    : GfMenuObject(handle), m_items(), m_index(0), m_list(nullptr), m_seq(this), m_confirmOpen(false),
      m_callContext(nullptr), m_idList(nullptr), m_str(), m_msgList(nullptr), m_number(), m_numberMax(), pad_200(),
      m_onlyIra(false), m_iraAddOn(false) {
    s_NoSaveData = true;
    m_idList = GfMenuIDList::create();
    ui::UIListInfoBase::SetupParam param;
    param.m_pageRowSize = 3;
    m_idList->setup(getAllocator(ALLOCATOR(0)), param);
    m_callContext = GfMenuCallContext::create();
    m_msgList = GfMenuMsgList::create();
    m_number = GfMenuReferenceNumber::create();
    m_numberMax = GfMenuReferenceNumber::create();
    if (ui::UIUtil::isEnableExpType(3) && !GfMenuManager::isOnlyIra()) {
        m_iraAddOn = true;
    }
    if (!s_NoSaveData && tl::TitleMain::sys()->m_newGameAdv) {
        m_onlyIra = GfMenuObjUtil::isValidExpansion(3) && GfMenuManager::isOnlyIra();
    }
}

bool GfMenuObjTitle::isEnableNewGameAdv() {
    if (s_NoSaveData) {
        return false;
    }
    return tl::TitleMain::sys()->m_newGameAdv;
}

GfMenuObjTitle::~GfMenuObjTitle() {
    m_number = nullptr;
    m_numberMax = nullptr;
    if (m_msgList != nullptr) {
        m_msgList->release();
        m_msgList = nullptr;
    }
    if (m_callContext != nullptr) {
        m_callContext->release();
        m_callContext = nullptr;
    }
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

void GfMenuObjTitle::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjTitle::update() {
    m_seq.update();
    GfMenuObject::update();
}

bool GfMenuObjTitle::attach(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x18));
    if (acc.m_object == nullptr) {
        return false;
    }
    GfMenuObject::startCallContext(context, 0x18, acc.m_handle);
    return true;
}

bool GfMenuObjTitle::isEnableNewGame() {
    return true;
}

bool GfMenuObjTitle::isEnableContinue() {
    return !s_NoSaveData;
}

bool GfMenuObjTitle::isEnableOption() {
    return true;
}

bool GfMenuObjTitle::isEnableEventsTheater() {
    return !s_NoSaveData;
}

void GfMenuObjTitle::moveCursor(unsigned int handle, int index) {
    ui::UIObjectAcc item(handle, s_titleItems[m_items[index]].m_name);
    ui::UIObjectAcc cursor(handle, "LAY_Cursor");
    if (item.m_object != nullptr && cursor.m_object != nullptr) {
        GfMenuObjUtil::setDockPos(cursor.m_handle, item.m_handle, 0, true);
    }
}

bool GfMenuObjTitle::seqAocError() {
    if (!m_confirmOpen) {
        GfMenuManager::openCommonWindow(0x11B);
        m_confirmOpen = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    {
        ui::UIObjectAcc acc(m_handle, "LAY_main");
        ui::EventData event;
        event.m_type = 0x101;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
    m_confirmOpen = false;
    return true;
}

bool GfMenuObjTitle::seqConfirmNewGame() {
    if (!m_confirmOpen) {
        GfMenuManager::openCommonWindow(0xE1);
        m_confirmOpen = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    {
        ui::UIObjectAcc acc(m_handle, "LAY_main");
        unsigned short result = GfMenuManager::getCommonWindowResult();
        if (result == 0) {
            m_seq.addJob(&GfMenuObjTitle::seqSelectDifficulity);
        } else {
            ui::EventData event;
            event.m_type = 0x101;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
    m_confirmOpen = false;
    return true;
}

bool GfMenuObjTitle::seqConfirmAdvancedNewGame() {
    if (!m_confirmOpen) {
        GfMenuManager::openCommonWindow(0x116);
        m_confirmOpen = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    {
        ui::UIObjectAcc acc(m_handle, "LAY_ang_info");
        unsigned short result = GfMenuManager::getCommonWindowResult();
        if (result == 0) {
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            m_seq.addJob(&GfMenuObjTitle::seqSelectDifficulity);
        } else {
            GfMenuObject::enableInput(acc.m_handle);
        }
    }
    m_confirmOpen = false;
    return true;
}

bool GfMenuObjTitle::seqTipsDifficulity() {
    if (!m_confirmOpen) {
        GfMenuManager::openCommonWindow(0x10A);
        m_confirmOpen = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    {
        ui::UIObjectAcc acc(m_handle, "LAY_main");
        GfMenuObject::addResultCallContext(acc.m_handle, m_index, 0);
    }
    m_confirmOpen = false;
    return true;
}

}  // namespace gf

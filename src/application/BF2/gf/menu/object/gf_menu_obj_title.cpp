#include "classes/tl/TitleMain.h"
#include "classes/gf/GfMenuObjTitle.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuMsgList.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjOption.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfDataBtlDif.h"
#include "gf/GfGameUtilSaveData.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/SDataOption.h"
#include "gf/SDataSaveIra.h"
#include "mm/Rect.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIUtil.h"
#include "ui/UIStr.h"

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
      m_callContext(nullptr), m_idList(nullptr), m_str(), m_msgList(nullptr), m_number(), m_numberMax(), m_infoPage(0),
      m_infoDir(0), m_onlyIra(false), m_iraAddOn(false) {
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

void GfMenuObjTitle::initialize() {
    ui::UIObjectAcc root(m_handle);
    unsigned int main = root.searchChild("LAY_main");
    if (ui::UIObjectAcc(main).m_object != nullptr) {
#line 194
        ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0x18, main);
        unsigned int keywait = root.searchChild("LAY_keywait");
        GfMenuObject::migrateInput(root.searchChild("LAY_list"), main);
        GfMenuObject::migrateInput(keywait, main);
    }
    s_NoSaveData = tl::TitleMain::sys()->getSaveBuffer()->m_system.m_version != 0x3A15B;
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        root.setDispChild(!s_NoSaveData, "IMG_Logo");
    }
    {
        mm::mtl::IAllocator* allocator = getAllocator(ALLOCATOR(0));
        ui::UISelectObjList::CreateParam create;
        create.m_allocator = allocator;
        m_list = ui::UISelectObjList::create(create);
    }
    m_items.clear();
    for (unsigned int i = 0; i < 5; i++) {
        ui::UIObjectAcc item(root.m_handle, s_titleItems[i].m_name);
        if (item.m_object != nullptr) {
            if (s_titleItems[i].m_isEnable()) {
                item.setDisp(true);
                m_items.push_back(i);
                m_list->addObject(item.m_handle);
            } else {
                item.setDisp(false);
            }
        }
    }
    {
        ui::UIObjectAcc list(main);
        mm::Rect<short> option;
        list.getLayoutRect("option", option);
        mm::Rect<short> theater;
        list.getLayoutRect("theater", theater);
        GfMenuObjUtil::placeObjectV(m_list, mm::Pnt<short>(option.x + option.w / 2, option.y + option.h / 2),
                                    theater.y - option.y);
    }
    {
        ui::UIObjectAcc version(main, "TXT_version_num");
        version.setText(ui::UIStr(GfMenuManager::getGameVersionString(), false));
    }
    {
        ui::UIObjectAcc info(main, "LAY_ang_info");
        GfMenuObject::disableInput(info.m_handle);
#line 262
        InfoListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) InfoListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(info.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        unsigned int rows = info.countChild("LAY_ang_info@%02d", 1);
        unsigned char* fp = GfDataBdat::getFP(GfMenuObjUtil::isValidExpansion(3) ? 0x16B : 0x16A);
        if (rows != 0 && fp != nullptr) {
            ui::UIListInfoBase::SetupParam param;
            param.m_pageRowSize = rows;
            m_msgList->setup(getAllocator(ALLOCATOR(0)), param);
            m_msgList->setBdat(GfMenuObjUtil::isValidExpansion(3) ? 0x16B : 0x16A, 0x13A);
            unsigned int pages = Bdat::getIdCount(fp) / (rows + 1);
            m_number->setValue(0);
            m_numberMax->setValue(pages);
        }
        GfMenuReferenceAdapter* page = GfMenuReferenceAdapter::create(info.searchChild("TXT_ang_info_page_num"), m_number, true);
        if (page != nullptr) {
            page->m_offset = 1;
        }
        GfMenuReferenceAdapter::create(info.searchChild("TXT_ang_info_page_max"), m_numberMax, true);
    }
    if (m_onlyIra) {
        ui::UIObjectAcc announce(main, "LAY_announce");
#line 306
        AnnounceListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) AnnounceListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(announce.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::initialize();
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

void GfMenuObjTitle::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        {
            ui::UIObjectAcc cursor(acc.m_handle, "LAY_keywait_cursor");
            GfMenuObjUtil::setDockPos(cursor.m_handle, acc.searchChild("TXT_keywait"), 0, true);
        }
        setDispMode(handle, 0);
        setInputMode(handle, 0);
        m_state = 0;
        if (m_owner->m_iraAddOn) {
            ui::UIObjectAcc base(acc.m_handle, "IMG_game_change_base");
            base.startAnimation(GfGameManager::isGameTypeIra() ? "original" : "ira", false);
            acc.setDispChild(true, "LAY_game_change");
        }
        acc.setDisp(true);
        break;
    case 2:
        GfMenuObject::termCallContext(handle);
        acc.setTerm();
        break;
    case 6:
        if (m_state == 1 && event.m_param0 != -1) {
            int index = event.m_param0;
            int prev = event.m_param1;
            if (!m_owner->m_iraAddOn) {
                if (prev != -1) {
                    ui::UIObjectAcc item(m_owner->m_list->getObject(prev));
                    item.loadDefColor();
                    item.setBorderWeight(2.0f);
                }
                m_owner->moveCursor(handle, index);
                {
                    ui::UIObjectAcc item(m_owner->m_list->getObject(index));
                    GfMenuObjUtil::setColMulandAdd(item.m_handle, "txt_title_sel");
                    item.setBorderWeight(2.0f);
                }
                if (index != prev) {
                    GfMenuObjUtil::playSECommonCursor();
                }
            } else {
                if (prev != -1) {
                    if (prev == m_owner->m_list->getSize()) {
                        ui::UIObjectAcc base(acc.m_handle, "IMG_game_change_base");
                        base.startAnimation(GfGameManager::isGameTypeIra() ? "original" : "ira", false);
                    } else {
                        ui::UIObjectAcc item(m_owner->m_list->getObject(prev));
                        item.loadDefColor();
                        item.setBorderWeight(2.0f);
                    }
                }
                if (index == m_owner->m_list->getSize()) {
                    ui::UIObjectAcc base(acc.m_handle, "IMG_game_change_base");
                    base.startAnimation(GfGameManager::isGameTypeIra() ? "original_sel" : "ira_sel", false);
                    acc.setDispChild(false, "LAY_Cursor");
                } else {
                    acc.setDispChild(true, "LAY_Cursor");
                    m_owner->moveCursor(handle, index);
                    ui::UIObjectAcc item(m_owner->m_list->getObject(index));
                    GfMenuObjUtil::setColMulandAdd(item.m_handle, "txt_title_sel");
                    item.setBorderWeight(2.0f);
                }
                if (index != prev) {
                    GfMenuObjUtil::playSECommonCursor();
                }
            }
        }
        break;
    case 8: {
        int state = m_state;
        if (event.m_param1 == 1) {
            if (state == 1) {
                if (m_owner->m_iraAddOn && m_owner->m_list->getSize() == event.m_param0) {
                    tl::TitleMain::sys()->m_reqChangeGameType = true;
                    GfMenuObject::disableInput(acc.m_handle);
                    GfMenuObjUtil::playSECommonDecide();
                    break;
                }
                unsigned int item = m_owner->m_items[event.m_param0];
                if (!s_NoSaveData && (item == 0 || item == 4)) {
                    if (item == 4) {
                        GfMenuManager::isOnlyIra();  // its answer is not used
                        if (!tl::TitleMain::sys()->isValidAocVersion()) {
                            m_owner->m_confirmOpen = false;
                            m_owner->m_seq.clear();
                            m_owner->m_seq.addJob(&GfMenuObjTitle::seqAocError);
                        } else {
                            if (m_owner->m_onlyIra) {
                                GfMenuObject::sendOpenEvent(acc.searchChild("LAY_announce"), 0, 0.0f);
                            } else {
                                GfMenuObject::sendOpenEvent(acc.searchChild("LAY_ang_info"), 0, 0.0f);
                            }
                        }
                    } else if (item == 0) {
                        m_owner->m_confirmOpen = false;
                        m_owner->m_seq.clear();
                        m_owner->m_seq.addJob(&GfMenuObjTitle::seqConfirmNewGame);
                    }
                } else if (item == 0 || item == 4) {
                    m_owner->m_confirmOpen = false;
                    m_owner->m_seq.clear();
                    m_owner->m_seq.addJob(&GfMenuObjTitle::seqSelectDifficulity);
                } else {
                    if (item == 1 || item == 3) {
                        GfMenuManager::isOnlyIra();  // its answer is not used
                        if (!tl::TitleMain::sys()->isValidAocVersion()) {
                            m_owner->m_confirmOpen = false;
                            m_owner->m_seq.clear();
                            m_owner->m_seq.addJob(&GfMenuObjTitle::seqAocError);
                            goto decided;
                        }
                    }
                    GfMenuObject::addResultCallContext(handle, item, 0);
                }
            decided:
                m_owner->m_index = item;
                m_state = 2;
                GfMenuObject::disableInput(acc.m_handle);
            }
        } else if (event.m_param1 == 2) {
            if (state == 1) {
                setDispMode(handle, 0);
                setInputMode(handle, 0);
                m_state = 0;
            }
        } else if (state == 0) {
            setDispMode(handle, 1);
            setInputMode(handle, 1);
            m_state = 1;
            unsigned int cursor = 0;
            for (unsigned int i = 0; i < m_owner->m_items.size(); i++) {
                if (m_owner->m_items[i] == 1) {
                    cursor = i;
                    break;
                }
            }
            if (m_owner->m_iraAddOn) {
                GfMenuObject::setupInputSelection(acc.searchChild("LAY_list"), cursor,
                                                  static_cast<unsigned int>(m_owner->m_items.size()) + 1);
            } else {
                GfMenuObject::setupInputSelection(acc.searchChild("LAY_list"), cursor,
                                                  static_cast<unsigned int>(m_owner->m_items.size()));
            }
        }
        if (state != m_state) {
            if (m_state == 1) {
                GfMenuObjUtil::playSECommonDecide();
            } else {
                GfMenuObjUtil::playSECommonFromInput(event.m_param1);
            }
        }
        break;
    }
    case 0x101:
        m_state = 1;
        GfMenuObject::enableInput(acc.m_handle);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjTitle::setDispMode(unsigned int handle, int mode) {
    GfMenuObjUtil::setChildDisp(handle, "LAY_keywait", mode == 0);
    GfMenuObjUtil::setChildDisp(handle, "LAY_list", mode == 1);
}

void GfMenuObjTitle::setInputMode(unsigned int handle, int mode) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object != nullptr) {
        if (mode == 0) {
            GfMenuObject::enableInput(acc.searchChild("LAY_keywait"));
            GfMenuObject::disableInput(acc.searchChild("LAY_list"));
        } else if (mode == 1) {
            GfMenuObject::enableInput(acc.searchChild("LAY_list"));
            GfMenuObject::disableInput(acc.searchChild("LAY_keywait"));
        }
    }
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

void GfMenuObjTitle::InfoListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::open(acc.m_handle, 0, 0, 0);
            GfMenuObjOperationInfo::setGuideDisp(false);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, false);
        } else if (event.m_param0 == 2) {
            if (!m_owner->m_onlyIra) {
                ui::UIObjectAcc main(m_owner->m_handle, "LAY_main");
                ui::EventData close;
                close.m_type = 0x101;
                close.m_param0 = m_result;
                GfMenuObject::sendEvent(main.m_handle, close, 0.0f);
            }
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            m_owner->m_confirmOpen = false;
            m_owner->m_seq.clear();
            m_owner->m_seq.addJob(&GfMenuObjTitle::seqConfirmAdvancedNewGame);
            GfMenuObject::disableInput(acc.m_handle);
        } else if (event.m_param1 == 2) {
            if (m_page == 0) {
                GfMenuObjUtil::playSECommonCancel();
                GfMenuObject::disableInput(acc.m_handle);
                if (m_owner->m_onlyIra) {
                    GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_announce"), 0, 0.0f);
                } else {
                    GfMenuObjOperationInfo::close();
                }
                GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
            } else {
                m_owner->m_infoPage = m_page - 1;
                m_owner->m_infoDir = 1;
                m_owner->m_confirmOpen = false;
                m_owner->m_seq.clear();
                m_owner->m_seq.addJob(&GfMenuObjTitle::seqInfoFadeOut);
                m_owner->m_seq.addJob(&GfMenuObjTitle::seqInfoFadeIn);
                GfMenuObject::disableInput(acc.m_handle);
                m_page--;
                m_owner->m_number->setValue(m_page);
                GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, false);
                GfMenuObjUtil::playSE(0xD);
            }
        } else if (event.m_param1 == 9) {
            if (m_page + 1 < m_owner->m_numberMax->m_value) {
                int page = m_page + 1;
                m_owner->m_infoPage = page;
                m_owner->m_infoDir = 0;
                m_owner->m_confirmOpen = false;
                m_owner->m_seq.clear();
                m_owner->m_seq.addJob(&GfMenuObjTitle::seqInfoFadeOut);
                m_owner->m_seq.addJob(&GfMenuObjTitle::seqInfoFadeIn);
                GfMenuObject::disableInput(acc.m_handle);
                m_page = page;
                m_owner->m_number->setValue(m_page);
                GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, page + 1 == m_owner->m_numberMax->m_value);
                GfMenuObjUtil::playSE(0xD);
            }
        }
        break;
    case 0x21:
        m_owner->updateInfoPage(0);
        m_owner->refreshInfo(0);
        m_page = 0;
        m_result = 0;
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 0);
        break;
    case 0x22:
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
        GfMenuObjOperationInfo::close();
        break;
    }
}

void GfMenuObjTitle::updateInfoPage(unsigned int page) {
    unsigned char* fp = GfDataBdat::getFP(GfMenuObjUtil::isValidExpansion(3) ? 0x16B : 0x16A);
    if (fp == nullptr) {
        return;
    }
    int rowSize = m_msgList->getPageRowSize();
    int top = Bdat::getIdTop(fp);
    m_msgList->clear();
    for (unsigned int i = 0; i < m_msgList->getPageRowSize() + 1; i++) {
        unsigned int list = GfMenuObjUtil::isValidExpansion(3) ? 0x16B : 0x16A;
        unsigned int id = top + page * rowSize + page + i;
        unsigned short msg = GfMenuObjUtil::getMsgIDFromList(list, id);
        if (msg == 0) {
            continue;
        }
        if (i == 0) {
            ui::UIStr str(GfDataBdat::getFP(0x13A), msg);
            m_str.copy(str);
        } else {
            MsgID content;
            content.m_id = id;
            content.m_sortKey = 0;
            m_msgList->addContents(MsgID(content));
        }
    }
}

void GfMenuObjTitle::refreshInfo(unsigned int) {
    ui::UIStr str;
    mm::mtl::FixStr<32> name;
    {
        ui::UIObjectAcc title(m_handle, "TXT_ang_info_title");
        title.setText(m_str);
        title.setDisp(m_str.isValid());
    }
    for (unsigned int i = 0; i < m_msgList->getPageRowSize(); i++) {
        name.format("LAY_ang_info@%02d", i + 1);
        ui::UIObjectAcc row(m_handle, name.m_str);
        if (row.m_object == nullptr) {
            continue;
        }
        bool valid = m_msgList->getMsg(i, str, false);
        if (valid) {
            name.format("TXT_ang_info@%02d", i + 1);
            ui::UIObjectAcc text(m_handle, name.m_str);
            if (text.m_object != nullptr) {
                text.setText(str);
            }
        }
        row.setDisp(valid);
    }
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

bool GfMenuObjTitle::seqInfoFadeOut() {
    ui::UIObjectAcc list(m_handle, "LAY_ang_info_list");
    bool done = false;
    if (!m_confirmOpen) {
        if (m_infoDir == 0) {
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 0.3f;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_r";
            param.m_setDefault = true;
            GfMenuObjUtil::startCtrl(list.m_handle, param, nullptr);
        } else {
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 0.3f;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_l";
            param.m_setDefault = true;
            GfMenuObjUtil::startCtrl(list.m_handle, param, nullptr);
        }
        {
            ui::UIObjectAcc title(m_handle, "TXT_ang_info_title");
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 0.3f;
            param.m_methods = 2;
            GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
        }
        m_confirmOpen = true;
    } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(list.m_handle))) {
        updateInfoPage(m_infoPage);
        refreshInfo(m_infoPage);
        m_confirmOpen = false;
        done = true;
    }
    return done;
}

bool GfMenuObjTitle::seqInfoFadeIn() {
    ui::UIObjectAcc list(m_handle, "LAY_ang_info_list");
    bool done = false;
    if (m_confirmOpen) {
        if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(list.m_handle))) {
            ui::UIObjectAcc info(m_handle, "LAY_ang_info");
            GfMenuObject::enableInput(info.m_handle);
            done = true;
        }
        return done;
    }
    if (m_infoDir == 0) {
        GfMenuObjUtil::CtrlParam param;
        param.m_time = 0.3f;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(list.m_handle, param, nullptr);
    } else {
        GfMenuObjUtil::CtrlParam param;
        param.m_time = 0.3f;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r";
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(list.m_handle, param, nullptr);
    }
    {
        ui::UIObjectAcc title(m_handle, "TXT_ang_info_title");
        GfMenuObjUtil::CtrlParam param;
        param.m_time = 0.3f;
        param.m_methods = 1;
        GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
    }
    m_confirmOpen = true;
    return false;
}

void GfMenuObjTitle::AnnounceListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        unsigned char* fp = GfDataBdat::getFP(0x10C);
        unsigned char* text = GfDataBdat::getFP(0x13B);
        unsigned short title = Bdat::getVal(fp, "title", 1);
        unsigned short summary = Bdat::getVal(fp, "summary", 1);
        ui::UIObjectAcc(acc.m_handle, "TXT_page_index").setText(ui::UIStr(text, title));
        ui::UIObjectAcc(acc.m_handle, "TXT_page_summary").setText(ui::UIStr(text, summary));
        acc.setDisp(false);
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::open(acc.m_handle, 0, 0, 0);
            GfMenuObjOperationInfo::setGuideDisp(false);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, false);
        }
        break;
    case 8:
        if (event.m_param1 == 9) {
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_ang_info"), 0, 0.0f);
            GfMenuObjUtil::playSECommonDecide();
        } else if (event.m_param1 == 2) {
            ui::UIObjectAcc main(m_owner->m_handle, "LAY_main");
            ui::EventData close;
            close.m_type = 0x101;
            GfMenuObject::sendEvent(main.m_handle, close, 0.0f);
            GfMenuObjUtil::playSECommonCancel();
            GfMenuObjOperationInfo::close();
        } else {
            break;
        }
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
        break;
    case 0x21:
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 0);
        break;
    case 0x22:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
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

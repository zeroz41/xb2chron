#include "classes/gf/GfMenuObjTips.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfMenuObjBtlchTelop.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuTypes.h"

namespace gf {

// 2.0.0's symbols name it (lbl_7100EAB930)
bool GfMenuObjTips::s_Open;

GfMenuObjTips::GfMenuObjTips(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_mainSeq(this), m_context(nullptr), m_reserved(nullptr), m_idList(nullptr),
      m_fromLayer(false), m_onlyIra(false) {
    m_context = GfMenuCallContext::create();
    m_idList = GfMenuIDList::create();
    s_Open = true;
}

GfMenuObjTips::~GfMenuObjTips() {
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    s_Open = false;
}

void GfMenuObjTips::registStartTutorialID(unsigned int menuId) {
    GfMenuTypes::Param param;
    param.m_menuId = menuId;
    GfMenuFullScreen::registLayerParam(0x12E, param);
}

void GfMenuObjTips::start(unsigned int param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x89));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc tutorial(acc.m_handle, "LAY_tutorial");
        GfMenuObject::sendOpenEvent(tutorial.m_handle, param, 0.0f);
    }
}

void GfMenuObjTips::unlockTips(unsigned int id) {
    unsigned char* fp = GfDataBdat::getFP(0x102);
    if (fp == nullptr || id < Bdat::getIdTop(fp)) {
        return;
    }
    fp = GfDataBdat::getFP(0x102);
    if (fp == nullptr) {
        return;
    }
    int index = id - Bdat::getIdTop(fp) + 0xEF05;
    GfGameFlag::setLocal(2, index, (GfGameFlag::getLocal(2, index) & 0xFFFE) | 1);
}

void GfMenuObjTips::setTipsNoView(unsigned int id) {
    unsigned char* fp = GfDataBdat::getFP(0x102);
    if (fp == nullptr || id < Bdat::getIdTop(fp)) {
        return;
    }
    fp = GfDataBdat::getFP(0x102);
    if (fp == nullptr) {
        return;
    }
    int index = id - Bdat::getIdTop(fp) + 0xEF05;
    GfGameFlag::setLocal(2, index, GfGameFlag::getLocal(2, index) & 0xFFFD);
}

void GfMenuObjTips::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x89, main.m_handle);
    if (GfMenuObjUtil::getMenuCondition(0x3A)) {
        main.setDispChild(true, "IMG_add_a@02");
        main.setDispChild(true, "IMG_add@04");
    }
    if (GfMenuObjUtil::getMenuCondition(0x3A)) {
        main.setDispChild(true, "IMG_add_b@02");
    }
    if (GfMenuObjUtil::getMenuCondition(0x3C)) {
        main.setDispChild(true, "IMG_add_a@03");
    }
    if (GfMenuObjUtil::getMenuCondition(0x3D)) {
        main.setDispChild(true, "IMG_add_b@03");
    }
    if (GfMenuObjUtil::getMenuCondition(0x3E)) {
        main.setDispChild(true, "IMG_add_c@03");
    }
    if (GfMenuObjUtil::getMenuCondition(0x3F)) {
        main.setDispChild(true, "IMG_add_d@03");
    }
    if (GfMenuObjUtil::getMenuCondition(0x40)) {
        main.setDispChild(true, "IMG_add_a@05");
    }
    {
        ui::UIObjectAcc tutorial(main.m_handle, "LAY_tutorial");
#line 244
        TutorialListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TutorialListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(tutorial.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObjUtil::createFitPlugin(main.searchChild("IMG_text_bg"), main.searchChild("LAY_text"), 0, 0,
                                       GfMenuObjUtil::FitOption());
        GfMenuObject::disableInput(tutorial.m_handle);
    }
    {
        ui::UIObjectAcc list(main.m_handle, "LAY_list");
        ui::UIListInfoBase::SetupParam setup;
        setup.m_pageRowSize = list.countChild("LAY_list_item@%02d", 1);
        setup.m_pageScroll = true;
        m_idList->setup(getAllocator(ALLOCATOR(0)), setup);
        GfMenuObjUtil::createVScrollBarPlugin(list.searchChild("IMG_list_scroll_bar"), m_idList, "IMG_list_scroll_base",
                                              true);
#line 278
        ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(list.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    int index = 0;
    {
        GfMenuTypes::Param param;
        if (GfMenuObject::getFSLayerParam(m_fsLayer, param)) {
            index = param.m_menuId;
            GfMenuObject::removeFSLayerParam(m_fsLayer);
            m_fromLayer = true;
        }
    }
    if (m_fromLayer) {
        ui::UIObjectAcc tutorial(main.m_handle, "LAY_tutorial");
        GfMenuObject::sendOpenEvent(tutorial.m_handle, index, 0.0f);
        GfMenuObjOperationInfo::open(0, 0, 0, 0);
        GfMenuObjOperationInfo::setGuideDisp(false);
    } else {
        ui::UIObjectAcc list(main.m_handle, "LAY_list");
        GfMenuObject::sendOpenEvent(list.m_handle, index, 0.0f);
        if (GfMenuManager::isClearCheck()) {
            m_onlyIra = GfMenuObjUtil::isValidExpansion(3) && GfMenuManager::isOnlyIra();
            if (m_onlyIra) {
                unsigned char* fp = GfDataBdat::getFP(0x10C);
                unsigned char* message = GfDataBdat::getFP(0x13B);
                unsigned short title = Bdat::getVal(fp, "title", 1);
                unsigned short summary = Bdat::getVal(fp, "summary", 1);
                ui::UIObjectAcc(main.m_handle, "TXT_page_index").setText(ui::UIStr(message, title));
                ui::UIObjectAcc(main.m_handle, "TXT_page_summary").setText(ui::UIStr(message, summary));
            }
        }
    }
    GfMenuObject::initialize();
}

void GfMenuObjTips::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjTips::update() {
    m_mainSeq.update();
    m_seq.update();
    GfMenuObject::update();
}

// Inferred helper (the name is not the original's): whether a tips id's row is unread, bit 1 of local game flag 2's
// entry id - top + 0xEF05 clear (BDAT table 0x102's id top); true for an id outside the table.
static inline bool isTipsUnread(unsigned int id) {
    unsigned char* fp = GfDataBdat::getFP(0x102);
    if (fp == nullptr || id < Bdat::getIdTop(fp)) {
        return true;
    }
    fp = GfDataBdat::getFP(0x102);
    if (fp == nullptr) {
        return true;
    }
    return (GfGameFlag::getLocal(2, id - Bdat::getIdTop(fp) + 0xEF05) & 2) == 0;
}

void GfMenuObjTips::refreshList(bool) {
    ui::UIObjectAcc list(m_handle, "LAY_list");
    mm::mtl::FixStr<32> name;
    unsigned char* fp = GfDataBdat::getFP(0x102);
    if (fp == nullptr) {
        return;
    }
    unsigned char* message = GfDataBdat::getFP(299);
    if (message == nullptr) {
        return;
    }
    for (unsigned int i = 0; i < m_idList->getPageRowSize(); i++) {
        unsigned int id = m_idList->getContents(m_idList->getPageIndex(i)).m_id;
        bool exists = id != 0;
        name.format("LAY_list_item@%02d", i + 1);
        ui::UIObjectAcc item(list.m_handle, name.m_str);
        item.setDisp(exists);
        if (exists) {
            name.format("TXT_list_item_text@%02d", i + 1);
            ui::UIObjectAcc text(item.m_handle, name.m_str);
            unsigned short title = Bdat::getVal(fp, "title", id);
            if (title != 0) {
                ui::UIStr str(message, title);
                text.setText(str);
            }
        }
        bool cursor = i == m_idList->getIndex(false) - m_idList->getRowOffset();
        name.format("IMG_list_item_cursor@%02d", i + 1);
        item.setDispChild(cursor, name.m_str);
        bool unread = isTipsUnread(id);
        name.format("IMG_list_item_new@%02d", i + 1);
        item.setDispChild(exists && unread, name.m_str);
    }
}

void GfMenuObjTips::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        unsigned char* fp = GfDataBdat::getFP(0x102);
        if (fp != nullptr && GfDataBdat::getFP(299) != nullptr) {
            int top = Bdat::getIdTop(fp);
            m_owner->m_idList->clear();
            for (int i = 0; i < Bdat::getIdCount(fp); i++) {
                int id = top + i;
                if (m_owner->isUnlockTipsID(id) && (unsigned short)Bdat::getVal(fp, "condition", id) == 0) {
                    MenuID entry;
                    entry.m_id = id;
                    entry.m_subId = 0;
                    entry.m_subId = (unsigned short)Bdat::getVal(fp, "page", id);
                    m_owner->m_idList->addContents(entry);
                }
            }
            m_owner->m_idList->sortFromWork(false);
            m_owner->m_idList->setIndex(0);
            acc.setDisp(false);
            GfMenuObjOperationInfo::setGuideText(0x4C, 0);
            GfMenuObjMainMenu2::setSubIndexText(0x21);
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_idList->setIndex(index);
            m_owner->refreshList(false);
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_idList);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        } else if (event.m_param0 == 3) {
            m_owner->returnFSSubLayer(m_owner);
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            if (event.m_param0 == -1 || m_owner->m_idList->getSize() == 0) {
                break;
            }
            unsigned int id = m_owner->m_idList->getContents(m_owner->m_idList->getIndex(false)).m_id;
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_tutorial"), id, 0.0f);
            GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
            GfMenuObjUtil::playSECommonDecide();
        } else if (event.m_param1 == 2) {
            GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 3, 0);
            GfMenuObjUtil::playSECommonCancel();
        } else {
            break;
        }
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
        break;
    case 0x21: {
        unsigned int id = event.m_param0;
        if (id != 0) {
            for (unsigned int i = 0; i < m_owner->m_idList->getSize(); i++) {
                if (m_owner->m_idList->getContents(i).m_id == id) {
                    m_owner->m_idList->setIndex(i);
                    break;
                }
            }
        }
        m_owner->refreshList(false);
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 0);
        break;
    }
    }
}

bool GfMenuObjTips::isUnlockTipsID(unsigned int id) {
    unsigned char* fp = GfDataBdat::getFP(0x102);
    if (fp == nullptr || id < Bdat::getIdTop(fp)) {
        return false;
    }
    fp = GfDataBdat::getFP(0x102);
    if (fp == nullptr) {
        return false;
    }
    if ((unsigned short)Bdat::getVal(fp, "page", id) == 0) {
        return m_onlyIra;
    }
    return GfGameFlag::getLocal(2, id - Bdat::getIdTop(fp) + 0xEF05) & 1;
}

void GfMenuObjTips::TutorialListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_textCount = acc.countChild("LAY_text@%02d", 1);
        m_textIndex = 0;
        acc.setDisp(false);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 0x21: {
        unsigned int id = event.m_param0;
        unsigned char* fp = GfDataBdat::getFP(0x102);
        if (fp == nullptr || Bdat::getIdTop(fp) > id) {
            fp = GfDataBdat::getFP(0x101);
            if (fp == nullptr) {
                break;
            }
        }
        unsigned char* message = GfDataBdat::getFP(299);
        if (message == nullptr) {
            break;
        }
        mm::mtl::FixStr<16> member;
        if (id == 0 || !GfMenuBdat::isValidBdatID(fp, id)) {
            break;
        }
        {
            ui::UIObjectAcc bg(acc.searchSibiling("LAY_bg"));
            bg.countChild("LAY_bg@%02d", 1);
            int bgType = static_cast<unsigned char>(Bdat::getVal(fp, "bg_type", id));
            bool show = !m_owner->m_fromLayer;
            if (!show) {
                bgType = 0;
            }
            mm::mtl::FixStr<32> name;
            name.format("LAY_bg@%02d", bgType);
            if (m_tipsId == 0 || m_bgType != bgType) {
                if (bgType != 0) {
                    GfMenuObjUtil::setCommonFadeIn(bg.searchChild(name.m_str), 0, 0);
                }
                if (m_tipsId != 0 && m_bgType != 0) {
                    name.format("LAY_bg@%02d", m_bgType);
                    GfMenuObjUtil::setCommonFadeOut(bg.searchChild(name.m_str), 0, 0);
                }
                m_bgType = bgType;
                bg.setAlpha(1.0f);
            }
        }
        unsigned short title = Bdat::getVal(fp, "title", id);
        ui::UIObjectAcc(acc.m_handle, "TXT_title").setText(ui::UIStr(message, title));
        ui::UIObjectAcc(acc.m_handle, "TXT_title_shadow").setText(ui::UIStr(message, title));
        float alpha = m_bgType > 1 ? 0.0f : 1.0f;
        ui::UIObjectAcc(acc.m_handle, "TXT_title").setAlpha(alpha);
        ui::UIObjectAcc(acc.m_handle, "TXT_title_shadow").setAlpha(alpha);
        int ctrl = GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_title"), 1, 1);
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        mm::mtl::FixStr<32> name;
        bool cond = false;
        if (Bdat::getMember(fp, "change_cond") != nullptr) {
            unsigned short condition = Bdat::getVal(fp, "change_cond", id);
            cond = condition != 0 && GfGameCond::isGameCond(condition);
        }
        int top = 0;
        int topY = 0;
        for (int i = 0; i < m_textCount; i++) {
            if (cond) {
                member.format("cond_window_y%d", i + 1);
            } else {
                member.format("window_y%d", i + 1);
            }
            short y = 0;
            if (Bdat::getMember(fp, member.m_str) != nullptr) {
                y = Bdat::getVal(fp, member.m_str, id);
            }
            if (cond) {
                member.format("cond_message%d", i + 1);
            } else {
                member.format("message%d", i + 1);
            }
            unsigned short text = Bdat::getMember(fp, member.m_str) != nullptr ? Bdat::getVal(fp, member.m_str, id) : 0;
            bool disp = false;
            if (y != 0 && GfMenuBdat::isValidBdatID(message, text)) {
                name.format("TXT_text@%02d", i + 1);
                ui::UIObjectAcc txt(acc.m_handle, name.m_str);
                ui::UIStr str(message, text);
                txt.setText(str);
                disp = true;
            }
            name.format("LAY_text@%02d", i + 1);
            ui::UIObjectAcc lay(acc.m_handle, name.m_str);
            lay.setDisp(disp);
            if (disp) {
                mm::Pnt<short> pos;
                lay.getPos(pos);
                pos.y = y;
                lay.setPos(pos);
                if (y > topY) {
                    topY = y;
                    top = i;
                }
            }
            name.format("IMG_text_arrow@%02d", i + 1);
            acc.setDispChild(false, name.m_str);
        }
        m_textIndex = top;
        GfMenuObject::releaseTimer(acc.m_handle);
        GfMenuObject::registTimer(acc.m_handle, 0, 0.5f, true);
        unsigned char* tips = GfDataBdat::getFP(0x102);
        if (tips != nullptr && Bdat::getIdTop(tips) <= id) {
            m_owner->setViewTipsID(id);
        }
        acc.setDisp(true);
        acc.setAlpha(1.0f);
        m_tipsId = id;
        break;
    }
    case 3:
        switch (event.m_param0) {
        case 1:
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            if (!m_owner->m_fromLayer) {
                unsigned int index = m_owner->m_idList->getIndex(false);
                unsigned int last = m_owner->m_idList->getSize() - 1;
                GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, index < last && !m_owner->m_fromLayer);
                GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, index != 0 && !m_owner->m_fromLayer);
                GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, false);
            } else {
                GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 2, false);
                GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, false);
                GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, false);
            }
            break;
        case 2: {
            ui::UIObjectAcc bg(acc.searchSibiling("LAY_bg"));
            int count = bg.countChild("LAY_bg@%02d", 1);
            mm::mtl::FixStr<32> name;
            for (unsigned int i = 0; i < count; i++) {
                name.format("LAY_bg@%02d", i + 1);
                bg.setDispChild(false, name.m_str);
            }
            m_tipsId = 0;
            if (m_owner->m_fromLayer) {
                GfMenuObjOperationInfo::close();
                ui::UIManager::get()->terminateLayer(m_owner->m_fsLayer, true);
            }
            break;
        }
        case 3: {
            unsigned int index = m_owner->m_idList->getIndex(false) + 1;
            m_owner->m_idList->setIndex(index);
            GfMenuObject::sendOpenEvent(
                acc.m_handle, m_owner->m_idList->getContents(m_owner->m_idList->getIndex(false)).m_id, 0.0f);
            break;
        }
        case 4: {
            unsigned int index = m_owner->m_idList->getIndex(false) - 1;
            m_owner->m_idList->setIndex(index);
            GfMenuObject::sendOpenEvent(
                acc.m_handle, m_owner->m_idList->getContents(m_owner->m_idList->getIndex(false)).m_id, 0.0f);
            break;
        }
        }
        break;
    case 8: {
        int type = event.m_param1;
        switch (type) {
        case 9:
            GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 3, 0);
            GfMenuObjUtil::playSECommonCursor();
            break;
        case 10:
            GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 4, 0);
            GfMenuObjUtil::playSECommonCursor();
            break;
        case 1:
        case 2:
            GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
            if (!m_owner->m_fromLayer) {
                GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_list"), m_tipsId, 0.0f);
            }
            {
                ui::UIObjectAcc bg(acc.searchSibiling("LAY_bg"));
                GfMenuObjUtil::setCommonFadeOut(bg.m_handle, 0, 0);
            }
            if (type == 1) {
                GfMenuObjUtil::playSECommonDecide();
            } else {
                GfMenuObjUtil::playSECommonCancel();
            }
            break;
        default:
            return;
        }
        if (!m_owner->m_mainSeq.m_jobs.empty()) {
            GfMenuObjBtlchTelop::forceClose();
            m_owner->m_mainSeq.clear();
        }
        GfMenuObject::disableInput(acc.m_handle);
        if (type == 1 || type == 2) {
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        }
        break;
    }
    case 0xB:
        break;
    }
}

void GfMenuObjTips::setViewTipsID(unsigned int id) {
    unsigned char* fp = GfDataBdat::getFP(0x102);
    if (fp == nullptr || id < Bdat::getIdTop(fp) || !isUnlockTipsID(id)) {
        return;
    }
    fp = GfDataBdat::getFP(0x102);
    if (fp == nullptr) {
        return;
    }
    int index = id - Bdat::getIdTop(fp) + 0xEF05;
    GfGameFlag::setLocal(2, index, (GfGameFlag::getLocal(2, index) & 0xFFFD) | 2);
}

}  // namespace gf

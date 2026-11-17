#include "classes/gf/GfMenuObjBtlchTelop.h"
#include "classes/gf/GfMenuObjBtlchTutorial.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjBtlTime.h"
#include "gf/GfMenuBdat.h"
#include "classes/ui/UIEventManager.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "ui/UIUtil.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuTypes.h"

namespace gf {

// 2.0.0's symbols name it (lbl_7100EAA1C8)
bool GfMenuObjBtlchTutorial::s_Open;

GfMenuObjBtlchTutorial::GfMenuObjBtlchTutorial(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_mainSeq(this), m_context(nullptr), m_telopParam(), m_idList(nullptr),
      m_fromLayer(false) {
    m_context = GfMenuCallContext::create();
    m_idList = GfMenuIDList::create();
    s_Open = true;
}

GfMenuObjBtlchTutorial::~GfMenuObjBtlchTutorial() {
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

void GfMenuObjBtlchTutorial::registStartTutorialID(unsigned int menuId) {
    GfMenuTypes::Param param;
    param.m_menuId = menuId;
    GfMenuFullScreen::registLayerParam(0x67, param);
}

void GfMenuObjBtlchTutorial::start(unsigned int param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x89));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc tutorial(acc.m_handle, "LAY_tutorial");
        GfMenuObject::sendOpenEvent(tutorial.m_handle, param, 0.0f);
    }
}

bool GfMenuObjBtlchTutorial::isOpen() {
    return s_Open;
}

void GfMenuObjBtlchTutorial::initialize() {
    {
        ui::UIObjectAcc acc(m_handle);
        acc.setDispPriority(ui::UIUtil::getGroupPriority(0));
    }
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x89, main.m_handle);
    {
        ui::UIObjectAcc tutorial(main.m_handle, "LAY_tutorial");
#line 111
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
#line 145
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
    } else {
        ui::UIObjectAcc list(main.m_handle, "LAY_list");
        GfMenuObject::sendOpenEvent(list.m_handle, index, 0.0f);
    }
    GfMenuObject::initialize();
}

void GfMenuObjBtlchTutorial::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBtlchTutorial::update() {
    m_mainSeq.update();
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjBtlchTutorial::refreshList() {
    ui::UIObjectAcc list(m_handle, "LAY_list");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_idList->getPageRowSize(); i++) {
        unsigned int id = m_idList->getContents(m_idList->getPageIndex(i)).m_id;
        bool exists = id != 0;
        name.format("LAY_list_item@%02d", i + 1);
        ui::UIObjectAcc item(list.m_handle, name.m_str);
        item.setDisp(exists);
        if (exists) {
            unsigned char* fp = GfDataBdat::getFP(0x101);
            if (fp == nullptr) {
                break;
            }
            unsigned char* message = GfDataBdat::getFP(299);
            if (message == nullptr) {
                break;
            }
            name.format("TXT_list_item_text@%02d", i + 1);
            ui::UIObjectAcc text(item.m_handle, name.m_str);
            ui::UIStr str(message, (unsigned short)Bdat::getVal(fp, "title", id));
            text.setText(str);
        }
        name.format("IMG_list_item_cursor@%02d", i + 1);
        item.setDispChild(i == m_idList->getIndex(false) - m_idList->getRowOffset(), name.m_str);
    }
}

void GfMenuObjBtlchTutorial::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        unsigned char* fp = GfDataBdat::getFP(0x101);
        if (fp == nullptr) {
            break;
        }
        unsigned char* message = GfDataBdat::getFP(299);
        if (message == nullptr) {
            break;
        }
        m_owner->m_idList->clear();
        for (int i = 0; i < Bdat::getIdCount(fp); i++) {
            int row = i + 1;
            unsigned short condition = Bdat::getVal(fp, "condition", row);
            if (condition == 0 || (condition != 1 && GfGameCond::isGameCond(condition))) {
                m_owner->m_idList->addContents(MenuID{static_cast<unsigned int>(row), 0});
            }
        }
        m_owner->m_idList->setIndex(0);
        acc.setDisp(false);
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_idList->setIndex(index);
            m_owner->refreshList();
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 3:
        switch (event.m_param0) {
        case 1:
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_idList);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            break;
        case 3:
            ui::UIManager::get()->terminateLayer(m_owner->m_fsLayer, true);
            break;
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
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
    case 0x21:
        m_owner->refreshList();
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 0);
        break;
    }
}

void GfMenuObjBtlchTutorial::TutorialListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_textCount = acc.countChild("LAY_text@%02d", 1);
        m_textIndex = 0;
        acc.setDisp(false);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 0x21: {
        int id = event.m_param0;
        unsigned char* fp = GfDataBdat::getFP(0x101);
        if (fp == nullptr) {
            break;
        }
        unsigned char* message = GfDataBdat::getFP(299);
        if (message == nullptr) {
            break;
        }
        mm::mtl::FixStr<16> member;
        if (id == 0 || !GfMenuBdat::isValidBdatID(fp, id)) {
            break;
        }
        unsigned short title = Bdat::getVal(fp, "title", id);
        ui::UIObjectAcc(acc.m_handle, "TXT_title").setText(ui::UIStr(message, title));
        ui::UIObjectAcc(acc.m_handle, "TXT_title_shadow").setText(ui::UIStr(message, title));
        int ctrl = GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_title"), 1, 1);
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        {
            ui::UIObjectAcc bg(acc.searchSibiling("LAY_bg"));
            bg.countChild("IMG_bg@%02d", 1);
            unsigned int bgType = static_cast<unsigned char>(Bdat::getVal(fp, "bg_type", id));
            mm::mtl::FixStr<32> name;
            name.format("IMG_bg@%02d", bgType + 1);
            if (m_tutorialId == 0 || m_bgType != bgType) {
                GfMenuObjUtil::setCommonFadeIn(bg.searchChild(name.m_str), 0, 0);
                if (m_tutorialId != 0) {
                    name.format("IMG_bg@%02d", m_bgType + 1);
                    GfMenuObjUtil::setCommonFadeOut(bg.searchChild(name.m_str), 0, 0);
                }
                m_bgType = bgType;
                bg.setAlpha(1.0f);
            }
        }
        unsigned char telop = Bdat::getVal(fp, "use_telop", id);
        if (telop != 0) {
            bool start = true;
            switch (telop) {
            case 1:
                m_owner->m_telopParam.m_type = 0;
                break;
            case 2:
                m_owner->m_telopParam.m_type = 3;
                m_owner->m_telopParam.m_value = 0;
                break;
            case 3:
                m_owner->m_telopParam.m_type = 3;
                m_owner->m_telopParam.m_value = 1;
                break;
            case 4:
                m_owner->m_telopParam.m_type = 3;
                m_owner->m_telopParam.m_value = 2;
                break;
            case 5:
                m_owner->m_telopParam.m_type = 1;
                m_owner->m_telopParam.m_value = 1;
                break;
            case 6:
                m_owner->m_telopParam.m_type = 2;
                m_owner->m_telopParam.m_value = 1;
                break;
            default:
                start = false;
                break;
            }
            if (start) {
                m_owner->m_mainSeq.clear();
                m_owner->m_mainSeq.addJob(&GfMenuObjBtlchTutorial::seqWaitLoading);
                m_owner->m_mainSeq.addJob(&GfMenuObjBtlchTutorial::seqStartTelop);
            }
        }
        if (static_cast<unsigned char>(Bdat::getVal(fp, "use_hud_time", id)) == 1) {
            GfMenuObjBtlTime::open(0, 0);
        }
        if (static_cast<unsigned char>(Bdat::getVal(fp, "use_hud_cube", id)) == 1) {
            GfMenuObjBtlTime::open(1, 0);
        }
        mm::mtl::FixStr<32> name;
        int maxY = 0;
        int textIndex = 0;
        for (int i = 0; i < m_textCount; i++) {
            member.format("window_y%d", i + 1);
            short y = 0;
            if (Bdat::getMember(fp, member.m_str) != nullptr) {
                y = Bdat::getVal(fp, member.m_str, id);
            }
            member.format("message%d", i + 1);
            unsigned short text =
                Bdat::getMember(fp, member.m_str) != nullptr ? Bdat::getVal(fp, member.m_str, id) : 0;
            bool disp = false;
            if (y != 0 && GfMenuBdat::isValidBdatID(message, text)) {
                name.format("TXT_text@%02d", i + 1);
                ui::UIObjectAcc textAcc(acc.m_handle, name.m_str);
                textAcc.setText(ui::UIStr(message, text));
                disp = true;
            }
            name.format("LAY_text@%02d", i + 1);
            ui::UIObjectAcc item(acc.m_handle, name.m_str);
            item.setDisp(disp);
            if (disp) {
                mm::Pnt<short> pos;
                item.getPos(pos);
                pos.y = y;
                item.setPos(pos);
                if (y > maxY) {
                    textIndex = i;
                    maxY = y;
                }
            }
            name.format("IMG_text_arrow@%02d", i + 1);
            acc.setDispChild(false, name.m_str);
        }
        m_textIndex = textIndex;
        GfMenuObject::releaseTimer(acc.m_handle);
        GfMenuObject::registTimer(acc.m_handle, 0, 0.5f, true);
        acc.setDisp(true);
        acc.setAlpha(1.0f);
        m_tutorialId = id;
        break;
    }
    case 3:
        switch (event.m_param0) {
        case 1: {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            unsigned int index = m_owner->m_idList->getIndex(false);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 1, false);
            unsigned int last = m_owner->m_idList->getSize() - 1;
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 9, index < last && !m_owner->m_fromLayer);
            GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, index != 0 && !m_owner->m_fromLayer);
            break;
        }
        case 2: {
            ui::UIObjectAcc bg(acc.searchSibiling("LAY_bg"));
            int count = bg.countChild("IMG_bg@%02d", 1);
            mm::mtl::FixStr<32> name;
            for (unsigned int i = 0; i < count; i++) {
                name.format("IMG_bg@%02d", i + 1);
                bg.setDispChild(false, name.m_str);
            }
            m_tutorialId = 0;
            if (m_owner->m_fromLayer) {
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
        if (type == 9) {
            GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 3, 0);
            GfMenuObjUtil::playSECommonCursor();
        } else if (type == 10) {
            GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 4, 0);
            GfMenuObjUtil::playSECommonCursor();
        } else if (type == 2) {
            GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
            if (!m_owner->m_fromLayer) {
                GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_list"), 0, 0.0f);
            }
            {
                ui::UIObjectAcc bg(acc.searchSibiling("LAY_bg"));
                GfMenuObjUtil::setCommonFadeOut(bg.m_handle, 0, 0);
            }
            GfMenuObjUtil::playSECommonCancel();
        } else {
            break;
        }
        if (!m_owner->m_mainSeq.m_jobs.empty()) {
            GfMenuObjBtlchTelop::forceClose();
            m_owner->m_mainSeq.clear();
        }
        GfMenuObjBtlTime::closeAll();
        GfMenuObject::disableInput(acc.m_handle);
        if (type == 2) {
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        }
        break;
    }
    case 0xB:
        break;
    }
}

bool GfMenuObjBtlchTutorial::seqStartTelop() {
    m_context->reset();
    GfMenuObjBtlchTelop::open(m_context, m_telopParam);
    m_mainSeq.addJob(&GfMenuObjBtlchTutorial::seqWaitTelop);
    return true;
}

bool GfMenuObjBtlchTutorial::seqWaitTelop() {
    if (!m_context->isTerm()) {
        return false;
    }
    m_mainSeq.addWait(4);
    m_mainSeq.addJob(&GfMenuObjBtlchTutorial::seqStartTelop);
    return true;
}

bool GfMenuObjBtlchTutorial::seqWaitLoading() {
    return !ui::UIManager::get()->isLoading();
}

}  // namespace gf

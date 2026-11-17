#include "classes/gf/GfMenuObjTips.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/ui/UIEventManager.h"
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

// ListListener::reciveEvent (0x710048845C) and TutorialListener::reciveEvent (0x7100488958) are not here yet

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

#include "classes/gf/GfMenuObjBtlchTelop.h"
#include "classes/gf/GfMenuObjBtlchTutorial.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
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

// ListListener::reciveEvent (0x71003B31C8) is not here yet: block placement differs

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

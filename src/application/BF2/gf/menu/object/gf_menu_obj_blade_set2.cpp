#include "classes/gf/GfMenuObjBladeSet2.h"
#include "classes/gf/GfMenuObjBladeSet2/MainListener.h"
#include "classes/gf/GfMenuObjBladeSet2/BladeSlotListener.h"
#include "classes/gf/GfMenuObjBladeSet2/BladeListListener.h"
#include "classes/gf/GfMenuObjBladeSet2.h"
#include "classes/gf/GfMenuObjBladeSet2/MainListener.h"
#include "classes/gf/GfMenuObjBladeSet2/BladeSlotListener.h"
#include "classes/gf/GfMenuObjBladeSet2/BladeListListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "ui/EventData.h"
#include "mm/mtl/Delegate.h"
#include "gf/GfMenuSequence.h"

namespace gf {

GfMenuObjBladeSet2::GfMenuObjBladeSet2(unsigned int handle)
    : GfMenuObject(handle), m_slotList(nullptr), pad_30(nullptr), m_bladeList(nullptr), pad_40(nullptr),
      m_driverList(nullptr), pad_50(nullptr), pad_58(0), m_context(nullptr), pad_68(0), pad_78(false),
      m_subContext(nullptr), pad_88(false), pad_8C(0), pad_90(0), pad_94(0), m_openType(0),
      m_seq(this), m_subSeq(this) {}

GfMenuObjBladeSet2::~GfMenuObjBladeSet2() {
    if (m_subContext != nullptr) {
        m_subContext->release();
        m_subContext = nullptr;
    }
    if (m_slotList != nullptr) {
        m_slotList->release();
        m_slotList = nullptr;
    }
    if (pad_30 != nullptr) {
        pad_30->release();
        pad_30 = nullptr;
    }
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
    if (pad_40 != nullptr) {
        pad_40->release();
        pad_40 = nullptr;
    }
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    if (pad_50 != nullptr) {
        pad_50->release();
        pad_50 = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void GfMenuObjBladeSet2::setCloseToReturn() {
    GfMenuTypes::Param param;
    param.m_menuId = 1;
    GfMenuFullScreen::registLayerParam(GfMenuObject::getMenuLayerID(0x1E), param);
}

void GfMenuObjBladeSet2::setCloseToFSClose() {
    GfMenuTypes::Param param;
    param.m_menuId = 2;
    GfMenuFullScreen::registLayerParam(GfMenuObject::getMenuLayerID(0x1E), param);
}

void GfMenuObjBladeSet2::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 187
    MainListener* mainListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, mainListener);
    if (mainListener != nullptr) {
        mainListener->release();
    }
    GfMenuObject::attachExternalCall(0x67, main);
    unsigned int team = acc.searchChild("LAY_dr_team");
#line 192
    BladeSlotListener* slotListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) BladeSlotListener(this);
    slotListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(team, slotListener);
    if (slotListener != nullptr) {
        slotListener->release();
    }
    unsigned int list = acc.searchChild("LAY_bl_list");
#line 196
    BladeListListener* listListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) BladeListListener(this);
    listListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(list, listListener);
    if (listListener != nullptr) {
        listListener->release();
    }
    m_slotList = GfMenuBladeList::create();
    m_bladeList = GfMenuBladeList::create();
    m_driverList = GfMenuDriverList::create();
    m_context = GfMenuCallContext::create();
    m_subContext = GfMenuCallContext::create();
    m_openType = 0;
    GfMenuTypes::Param param;
    if (GfMenuObject::getFSLayerParam(m_fsLayer, param)) {
        m_openType = param.m_menuId;
        GfMenuObject::removeFSLayerParam(m_fsLayer);
    }
    GfMenuObjCmnStatus::openDrStatus(0, 0);
    GfMenuObjCmnStatus::openBlStatus(1, -1);
    GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_scroll_bar"), m_bladeList, "IMG_scroll_base", true);
    m_faceCount = acc.countChild("LAY_bl_facelayout@%02d", 1);
    GfMenuObject::initialize();
}

void GfMenuObjBladeSet2::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBladeSet2::update() {
    m_seq.update();
    m_subSeq.update();
    GfMenuObject::update();
}

void GfMenuObjBladeSet2::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObjUtil::setChildIcon(acc.m_handle, "IMG_l_button", 0x14);
        GfMenuObjUtil::setChildIcon(acc.m_handle, "IMG_r_button", 0x15);
        GfMenuObjUtil::setChildIcon(acc.m_handle, "IMG_release_button", 10);
        acc.setDisp(true);
        setFadeIn(handle);
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setTerm();
            if (m_owner->m_openType == 1) {
                GfMenuObjMainMenu2::closeCharChange();
                GfMenuObject::returnFSSubLayer(m_owner);
            } else if (m_owner->m_openType == 0) {
                GfMenuObjCharSelect::returnSubMenu();
                GfMenuObject::returnFSSubLayer(m_owner);
            } else {
                GfMenuObject::closeFSLayer(acc.m_handle, true, true);
            }
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        GfMenuObjCmnStatus::closeDrStatus();
        GfMenuObjCmnStatus::closeBlStatus();
        setFadeOut(handle);
        break;
    case 0x41:
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjBladeSet2::seqReturnBlSlot() {
    ui::UIObjectAcc acc(m_handle, "LAY_dr_team");
    sendEvent(acc.m_handle, 0x101, 1);
    refreshBladeList();
    return true;
}
}  // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBladeSet2>(const mm::mtl::Delegate<bool()>*);

template bool gf::GfMenuSequence<gf::GfMenuObjBladeSet2, 8>::wait();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjBladeSet2, 8>>(const mm::mtl::Delegate<bool()>*);

namespace gf {

}  // namespace gf

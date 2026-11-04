#include "classes/gf/GfMenuObjPartyForm3.h"
#include "classes/gf/GfMenuObjPartyForm3/BGListener.h"
#include "classes/gf/GfMenuObjPartyForm3/DriverSelectListener.h"
#include "classes/gf/GfMenuObjPartyForm3/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfWeapon.h"
#include "classes/ui/UIEventManager.h"
#include "gf/GfPartySelect.h"
#include "mm/mtl/FixedVector.h"
#include "ui/EventData.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "mm/mtl/Delegate.h"
#include "gf/GfGameUtil.h"

namespace gf {

GfMenuObjPartyForm3::GfMenuObjPartyForm3(unsigned int handle)
    : GfMenuObject(handle),
      m_driverList(nullptr),
      m_openType(0),
      m_partyCount(0),
      m_standbyCount(0),
      m_select(0),
      m_moveIndex(-1),
      m_moving(false),
      m_seq(this),
      m_announceContext(nullptr),
      m_canRemoveAdd(true),
      pad_319(false) {
    for (unsigned long i = 0; i < 7; ++i) {
        m_numbers[i] = nullptr;
    }
}

GfMenuObjPartyForm3::~GfMenuObjPartyForm3() {
    for (mm::mtl::IntrusivePtr<GfMenuReferenceNumber>* it = m_numbers.begin(); it != m_numbers.end(); ++it) {
        *it = nullptr;
    }
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    if (m_announceContext != nullptr) {
        m_announceContext->release();
        m_announceContext = nullptr;
    }
}

void GfMenuObjPartyForm3::registOpenParam(const OpenParam& openParam) {
    GfMenuTypes::Param param;
    param.m_halves.m_type = openParam.m_value;
    GfMenuFullScreen::registLayerParam(GfMenuObject::getMenuLayerID(0x24), param);
}

void GfMenuObjPartyForm3::initialize() {
    m_canRemoveAdd = !GfGameCond::isGameCond(0xA70);
    {
        GfMenuTypes::Param param;
        if (GfMenuObject::getFSLayerParam(m_fsLayer, param)) {
            m_openType = param.m_halves.m_type;
            GfMenuObject::removeFSLayerParam(m_fsLayer);
        }
    }
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 181
    MainListener* mainListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, mainListener);
    if (mainListener != nullptr) {
        mainListener->release();
    }
    GfMenuObject::attachExternalCall(0x62, main);
    unsigned int bg = acc.searchChild("LAY_bg");
#line 187
    BGListener* bgListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) BGListener(this);
    bgListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(bg, bgListener);
    if (bgListener != nullptr) {
        bgListener->release();
    }
    unsigned int select = acc.searchChild("LAY_dr_select");
    DriverSelectListener* selectListener =
#line 191
        new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) DriverSelectListener(this);
    selectListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(select, selectListener);
    if (selectListener != nullptr) {
        selectListener->release();
    }
    m_driverList = GfMenuDriverList::create();
    m_partyCount = 0;
    m_standbyCount = 0;
    {
        mm::mtl::FixedVector<unsigned short, 32> list;
        GfPartySelect::getDriverList(list, GfPartySelect::LIST_TYPE(0), 0);
        m_partyCount = list.size();
        list.clear();
        GfPartySelect::getDriverList(list, GfPartySelect::LIST_TYPE(1), 0);
        m_standbyCount = list.size();
        GfMenuDriverList::PartySetup setup;
        setup.m_skipUnused = false;
        setup.m_convertDriver = false;
        setup.m_selectFlag = false;
        setup.m_type = 2;
        m_driverList->setupFromParty(setup);
    }
    if (m_driverList->getSize() == 1) {
        m_canRemoveAdd = false;
    }
    for (unsigned long i = 0; i < 7; ++i) {
        m_numbers[i] = GfMenuReferenceNumber::create();
        m_numbers[i]->m_value = 3;
    }
    GfMenuObject::disableInput(acc.searchChild("LAY_dr_select"));
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc(m_handle, "LAY_guest@01").setDisp(GfGameUtil::isEnableIraSatahiko());
        ui::UIObjectAcc(m_handle, "LAY_guest@02").setDisp(GfGameUtil::isEnableIraMilto());
        if (!GfMenuObjUtil::getMenuCondition(0x2F)) {
            m_canRemoveAdd = false;
        }
    }
    GfMenuObject::initialize();
}

void GfMenuObjPartyForm3::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjPartyForm3::update() {
    m_seq.update();
    GfMenuObject::update();
}

bool GfMenuObjPartyForm3::seqAnnounceChange() {
    if (GfMenuObjUtil::isValidExpansion(3) && m_openType == 2) {
        return true;
    }
    if (m_announceContext != nullptr) {
        return m_announceContext->isTerm();
    }
    m_announceContext = GfMenuCallContext::create();
    GfMenuObjCommonText::open(m_announceContext, 13, 0);
    return false;
}

bool GfMenuObjPartyForm3::seqWaitOpenEnd() {
    ui::UIObjectAcc acc(m_handle, "LAY_dr_select");
    GfMenuObject::enableInput(acc.m_handle);
    if (GfMenuObjUtil::isValidExpansion(3)) {
        GfMenuObjMainMenu2::setCloseKeyEnable(true);
    }
    return true;
}

void GfMenuObjPartyForm3::BGListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    ui::UIObjectAcc owner(m_owner->m_handle);
    switch (event.m_type) {
    case 1:
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}
}  // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPartyForm3>(const mm::mtl::Delegate<bool()>*);

namespace gf {

}  // namespace gf

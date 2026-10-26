#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/SelectionChecker.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuSoundManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "plugin/Bdat.h"

namespace gf {

unsigned int GfMenuObjMainMenu2::s_openMenuID;
bool GfMenuObjMainMenu2::s_worldMapOpen;
bool GfMenuObjMainMenu2::s_cancelEnable;
bool GfMenuObjMainMenu2::s_closeKeyLocked;
bool GfMenuObjMainMenu2::s_charMenuOpen;
unsigned char GfMenuObjMainMenu2::s_bgOpen;
unsigned int GfMenuObjMainMenu2::s_index;

GfMenuObjMainMenu2::GfMenuObjMainMenu2(unsigned int handle)
    : GfMenuObject(handle), pad_28(nullptr), m_context(nullptr), pad_38(0), pad_3C(-1), pad_40(-1), m_menuId(0),
      m_driverList(nullptr), m_bladeList(nullptr), m_checker(nullptr), pad_88(0), pad_8C(false), m_seq(this),
      m_jobStarted(false) {
    m_driverList = GfMenuDriverList::create();
    m_bladeList = GfMenuBladeList::create();
    m_checker = new (getAllocator(ALLOCATOR(0)), __FILE__, 210, 8) SelectionChecker;
    s_openMenuID = 0;
    s_charMenuOpen = false;
    s_bgOpen = 0;
}

GfMenuObjMainMenu2::~GfMenuObjMainMenu2() {
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    if (pad_28 != nullptr) {
        pad_28->release();
        pad_28 = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_checker != nullptr) {
        delete m_checker;
        m_checker = nullptr;
    }
    s_openMenuID = 0;
    s_bgOpen = 0;
}

void GfMenuObjMainMenu2::finalize() {
    GfMenuSoundManager::fadeInFieldBgm(1.0f);
    GfMenuObject::finalize();
}

void GfMenuObjMainMenu2::update() {
    if (m_menuId != 0x28) {
        s_openMenuID = m_menuId;
    }
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjMainMenu2::setCloseKeyEnable(bool enable) {
    if (GfMenuObjUtil::fn_710048FD30(3) && s_closeKeyLocked) {
        return;
    }
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        GfMenuObject::setInputActionEnable(acc.searchChild("LAY_close"), 3, enable);
    }
}

void GfMenuObjMainMenu2::setSystemKeyEnable(bool enable) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x106;
        event.m_param0 = enable;
        ui::UIManager::sys()->requestObjectEvent(acc.m_handle, event, 0.0f);
        s_cancelEnable = enable;
    }
}

void GfMenuObjMainMenu2::closeCharChange() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
        ui::EventData event;
        event.m_type = 0x22;
        ui::UIManager::sys()->requestObjectEvent(change.m_handle, event, 0.0f);
    }
}

bool GfMenuObjMainMenu2::isOpenCharMenu() {
    if (GfMenuObjUtil::fn_710048FD30(3) && s_charMenuOpen) {
        return true;
    }
    return s_openMenuID == 0x27 || s_openMenuID == 0x12D;
}

bool GfMenuObjMainMenu2::fn_7100432E2C() {
    return GfMenuObjUtil::fn_710048FD30(3) && s_bgOpen != 0;
}

bool GfMenuObjMainMenu2::fn_7100432E5C() {
    return s_worldMapOpen;
}

unsigned int GfMenuObjMainMenu2::fn_7100432E6C() {
    return GfMenuObjUtil::fn_710048FD30(3) ? s_index : 0;
}

void GfMenuObjMainMenu2::cancelEnableMainMenu(bool enable) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x106;
        event.m_param0 = enable;
        ui::UIManager::sys()->requestObjectEvent(acc.m_handle, event, 0.0f);
        s_cancelEnable = enable;
    }
}

void GfMenuObjMainMenu2::registOpenParam(const OpenParam& param) {
    GfMenuTypes::Param layer;
    layer.m_menuId = param.m_page;
    GfMenuFullScreen::registLayerParam(GfMenuFullScreen::getScreenLayerID(1), layer);
}

void GfMenuObjMainMenu2::setSubLayer(unsigned int layer) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        sendEvent(acc.m_handle, 0x108, layer);
    }
}

void GfMenuObjMainMenu2::setGuideText(unsigned int text) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        sendEvent(acc.m_handle, 0x10A, text);
    }
}

void GfMenuObjMainMenu2::dispCloseButton() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        sendEvent(acc.searchChild("LAY_close"), 0x10D, 0);
    }
}

void GfMenuObjMainMenu2::execMapJump() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x5F));
    if (acc.m_object != nullptr) {
        sendEvent(acc.m_handle, 0x10E, 0);
    }
}

bool SelectionChecker::isEnableSelect(unsigned int id, int select) {
    unsigned char* bdat = GfDataBdat::getFP(GfMenuObjUtil::fn_710048FD30(3) ? 0x180 : 0x17F);
    return GfMenuObjUtil::getMenuCondition(static_cast<unsigned short>(
        reinterpret_cast<unsigned long>(Bdat::getVal(bdat, "useCond", Bdat::getIdTop(bdat) + select))));
}

}  // namespace gf

#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/SelectionChecker.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjMainMenu2/ChrChangeListener.h"
#include "classes/gf/GfMenuObjMainMenu2/CloseListener.h"
#include "classes/gf/GfMenuObjMainMenu2/IndexListener.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReference.h"
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

void GfMenuObjMainMenu2::IndexListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        acc.searchChild("TXT_index");
        GfMenuObjUtil::setChildDisp(acc.m_handle, "LAY_index", false);
        acc.searchChild("TXT_index_shadow");
        GfMenuObjUtil::setChildDisp(acc.m_handle, "LAY_index", false);
        ui::UIObjectAcc icon(acc.searchChild("IMG_index_icon"));
        icon.setImageIndex(0);
        acc.setDisp(true);
    } else if (event.m_type == 0x102) {
        unsigned int index = event.m_param0;
        ui::UIObjectAcc title(acc.searchChild("LAY_title"));
        if (index != 0) {
            setContentsSubText(acc.searchChild("TXT_index"), index, acc.m_handle);
            setContentsSubText(acc.searchChild("TXT_index_shadow"), index, acc.m_handle);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 1;
            param.m_curve = 1;
            param.m_time = 0.3f;
            GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
            title.setDisp(true);
        } else {
            title.setDisp(false);
        }
        if (GfMenuObjUtil::fn_710048FD30(3)) {
            s_index = index;
        }
    } else if (event.m_type == 0x101) {
        int index = event.m_param0;
        unsigned char* fp = GfDataBdat::getFP(GfMenuObjUtil::fn_710048FD30(3) ? 0x180 : 0x17F);
        unsigned int id = m_owner->m_contentsIds[index];
        unsigned int text = (unsigned short)Bdat::getVal(fp, "subTitle", id);
        if (handle != 0) {
            ui::EventData sub;
            sub.m_type = 0x102;
            sub.m_param0 = text;
            ui::UIManager::sys()->requestObjectEvent(handle, sub, 0.0f);
        }
        unsigned int image = (unsigned short)Bdat::getVal(fp, "titleIcon", id);
        ui::UIObjectAcc icon(acc.searchChild("IMG_index_icon"));
        icon.setImageIndex(image);
    } else {
        UIObjectListener::reciveEvent(event, handle);
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

void GfMenuObjMainMenu2::ChrChangeListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        initChrChangeDr(owner, m_owner->m_driverList);
        initChrChangeBl(owner, m_owner->m_bladeList);
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        m_chr.m_state = 0;
        m_chr.m_listKind = -1;
        m_chr.m_subHandle = 0;
        break;
    case 3:
        switch (event.m_param0) {
        case 0:
            return;
        case 1:
            if (m_chr.m_listKind == 1 || m_chr.m_listKind == 2) {
                GfMenuObject::resetInputSelection(acc.m_handle);
                GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_bladeList);
            } else if (m_chr.m_listKind == 0) {
                GfMenuObject::resetInputSelection(acc.m_handle);
                GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_driverList);
            }
            if (m_owner->pad_88 != 0) {
                GfMenuObject::enableInput(acc.m_handle);
            } else {
                GfMenuObject::disableInput(acc.m_handle);
            }
            break;
        case 2:
            GfMenuObject::termCallContext(acc.m_handle);
            acc.setDisp(false);
            break;
        case 3:
            sendEvent(handle, 0x10C, 0);
            break;
        }
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        ChrChangeParam param;
        param.m_listKind = m_chr.m_listKind;
        param.m_target = m_owner->pad_88;
        param.m_driverList = m_owner->m_driverList;
        param.m_bladeList = m_owner->m_bladeList;
        inputChrChangeSub(acc, param, index);
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonTab();
        }
        break;
    }
    case 0x21: {
        int kind = event.m_param0;
        int mode = event.m_param2;
        m_owner->pad_88 = event.m_param1;
        ChrChangeParam param;
        if (kind == 3) {
            kind = 0;
            param.pad_2C = false;
        }
        param.m_listKind = kind;
        param.pad_04 = mode == 1;
        param.m_prevKind = m_chr.m_listKind;
        param.m_isOpen = m_chr.m_state == 1;
        param.m_target = m_owner->pad_88;
        param.m_driverList = m_owner->m_driverList;
        param.m_bladeList = m_owner->m_bladeList;
        param.m_driverId = GfMenuReference::getReferenceDriverID(0);
        param.m_subHandle = m_chr.m_subHandle;
        unsigned int sub = 0;
        if (openChrChangeSub(acc, param, sub)) {
            m_chr.m_state = 1;
            m_chr.m_listKind = kind;
            m_chr.m_subHandle = sub;
        }
        break;
    }
    case 0x22: {
        ChrChangeParam param;
        param.m_listKind = m_chr.m_listKind;
        closeChrChangeSub(acc, param);
        m_chr.m_state = 0;
        break;
    }
    case 0x109:
        m_owner->pad_88 = 0;
        break;
    case 0x10C: {
        ChrChangeParam param;
        param.m_listKind = m_chr.m_listKind;
        param.m_driverList = m_owner->m_driverList;
        param.m_bladeList = m_owner->m_bladeList;
        openChrChange2Sub(acc, param);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

namespace {
// Inferred name, not the original's: 3.0.1 and 1.0.0 both inline it into CloseListener::reciveEvent (no symbol);
// the frame shows an inlined helper (its event sits above the listener's own UI accessors). What it does: sends an
// event of that type to the main menu object attached at 0x5F, when there is one (as setSubLayer, setGuideText and
// execMapJump do with theirs).
inline void sendMainMenuEvent(unsigned short type) {
    ui::UIObjectAcc main(GfMenuObject::getAttachedObject(0x5F));
    if (main.m_object != nullptr) {
        ui::EventData event;
        event.m_type = type;
        ui::UIManager::sys()->requestObjectEvent(main.m_handle, event, 0.0f);
    }
}
}  // namespace

void GfMenuObjMainMenu2::CloseListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(handle);
        s_cancelEnable = false;
        s_closeKeyLocked = false;
        break;
    case 8:
        switch (event.m_param1) {
        case 2:
            if (!s_cancelEnable || GfMenuManager::isSwitchingFullScreen()) {
                break;
            }
            if (m_owner->m_menuId != 0) {
                GfMenuObject::returnFSSubLayer(handle, 1);
                sendMainMenuEvent(0x105);
                GfMenuObjUtil::playSECommonCancel();
                break;
            }
            sendEvent(owner.searchChild("LAY_main"), 0x107, 0);
            GfMenuObject::disableInput(handle);
            break;
        case 3:
            if (GfMenuManager::isSwitchingFullScreen()) {
                break;
            }
            sendEvent(owner.searchChild("LAY_main"), 0x107, 0);
            GfMenuObject::disableInput(handle);
            break;
        }
        break;
    case 0x21:
        GfMenuObject::enableInput(handle);
        s_cancelEnable = true;
        break;
    case 0x10D:
        GfMenuObjOperationInfo::open(handle, 0, 0, 0);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
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
        Bdat::getVal(bdat, "useCond", Bdat::getIdTop(bdat) + select)));
}

}  // namespace gf

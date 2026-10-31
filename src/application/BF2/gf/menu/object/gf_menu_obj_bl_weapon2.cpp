#include "gf/GfMenuTypes.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjBlWeapon2.h"
#include "classes/gf/GfMenuObjBlWeapon2/MainListener.h"
#include "classes/gf/GfMenuObjBlWeapon2/ItemSelectListener.h"
#include "classes/gf/GfMenuObjBlWeapon2/WeaponListener.h"
#include "classes/gf/GfMenuObjBlWeapon2/ChrChangeListener.h"
#include "classes/gf/GfMenuObjBlWeapon2.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjShop.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuObjBlWeapon2/ChrChangeListener.h"
#include "classes/gf/GfMenuObjBlWeapon2/ItemSelectListener.h"
#include "classes/gf/GfMenuObjBlWeapon2/MainListener.h"
#include "classes/gf/GfMenuObjBlWeapon2/WeaponListener.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfEquipUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjBlWeapon2::GfMenuObjBlWeapon2(unsigned int handle)
    : GfMenuObject(handle), m_items(nullptr), m_select(nullptr), m_chip(), m_charContext(nullptr),
      m_seq(this), m_seqStep(false), pad_2EC(0), m_openType(0), m_blades(nullptr), pad_300(false), pad_304(0) {
    m_context = GfMenuCallContext::create();
}

GfMenuObjBlWeapon2::~GfMenuObjBlWeapon2() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_items != nullptr) {
        m_items->release();
        m_items = nullptr;
    }
    if (m_select != nullptr) {
        m_select->release();
        m_select = nullptr;
    }
    m_chip = nullptr;
    if (m_charContext != nullptr) {
        m_charContext->release();
        m_charContext = nullptr;
    }
    if (m_blades != nullptr) {
        m_blades->release();
        m_blades = nullptr;
    }
}

void GfMenuObjBlWeapon2::initialize() {
    {
        GfMenuTypes::Param param;
        if (GfMenuObject::getFSLayerParam(m_fsLayer, param)) {
            m_openType = param.m_menuId & 0xFFFF;
            m_shop = param.m_menuId >> 16;
            GfMenuObject::removeFSLayerParam(m_fsLayer);
        } else {
            m_openType = 0;
        }
    }
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 173
    MainListener* mainListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, mainListener);
    if (mainListener != nullptr) {
        mainListener->release();
    }
    GfMenuObject::attachExternalCall(0x68, main);
    unsigned int chips = acc.searchChild("LAY_chips");
#line 178
    ItemSelectListener* itemListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ItemSelectListener(this);
    itemListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(chips, itemListener);
    if (itemListener != nullptr) {
        itemListener->release();
    }
    unsigned int weapon = acc.searchChild("LAY_weapon");
#line 182
    WeaponListener* weaponListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) WeaponListener(this);
    weaponListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(weapon, weaponListener);
    if (weaponListener != nullptr) {
        weaponListener->release();
    }
    unsigned int chrChange = acc.searchChild("LAY_chr_change");
#line 186
    ChrChangeListener* chrListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ChrChangeListener(this);
    chrListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(chrChange, chrListener);
    if (chrListener != nullptr) {
        chrListener->release();
    }
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_select = ui::UISelectObjList::create(create);
    m_items = GfMenuItemList::create();
    m_chip = GfMenuReferenceNumber::create();
    m_chip->m_value = 0;
    m_charContext = GfMenuCallContext::create();
    m_blades = GfMenuBladeList::create();
    GfMenuObject::disableInput(acc.searchChild("LAY_chips"));
    GfMenuObject::disableInput(acc.searchChild("LAY_chr_change"));
    GfMenuObject::initialize();
}

void GfMenuObjBlWeapon2::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBlWeapon2::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjBlWeapon2::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        acc.setDisp(true);
        GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_base"), 0, 0);
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_chips"), 0, 0.0f);
        GfMenuObject::sendOpenEvent(acc.searchChild("LAY_weapon"), 0, 0.0f);
        mm::mtl::FixStr<32> name;
        if (m_owner->m_openType == 1) {
            GfMenuBladeList::DriverSetup setup;
            setup.pad_1C = false;
            setup.pad_1D = false;
            setup.pad_1E = false;
            setup.m_type = 3;
            setup.m_driver = 0;
            setup.m_param.m_pageRowSize = 5;
            m_owner->m_blades->setupFromDriver(setup);
            GfMenuReference::setReferenceBladeID(0, m_owner->m_blades->getContents(0).m_blade);
            for (int i = 1; i < 7; i++) {
                name.format("LAY_menu@%02d", i);
                ui::UIObjectAcc menu(acc.searchChild(name.m_str));
                menu.setDisp(false);
                name.format("LAY_shop@%02d", i);
                ui::UIObjectAcc shop(acc.searchChild(name.m_str));
                shop.setDisp(true);
            }
            GfMenuObjCmnStatus::openBlStatus(1, -1);
        } else {
            for (int i = 1; i < 7; i++) {
                name.format("LAY_menu@%02d", i);
                ui::UIObjectAcc menu(acc.searchChild(name.m_str));
                menu.setDisp(true);
                name.format("LAY_shop@%02d", i);
                ui::UIObjectAcc shop(acc.searchChild(name.m_str));
                shop.setDisp(false);
            }
        }
        break;
    }
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setTerm();
            if (m_owner->m_openType == 0) {
                GfMenuObjCharSelect::returnSubMenu();
                GfMenuObject::returnFSSubLayer(m_owner);
            } else {
                GfMenuObject::termCallContext(handle);
                ui::UIManager::get()->terminateLayer(0x2D, true);
            }
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22: {
        int time = GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_base"), 2, 0);
        GfMenuObject::hookCtrlEvent(acc.m_handle, time);
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_chips"), 0, 0.0f);
        GfMenuObject::sendCloseEvent(acc.searchChild("LAY_weapon"), 0, 0.0f);
        if (m_owner->m_openType == 1) {
            GfMenuObjShop::dispBlade(false);
            GfMenuObjCmnStatus::closeBlStatus();
            unsigned int change = acc.searchChild("LAY_chr_change");
            ui::EventData close;
            close.m_type = 0x22;
            ui::UIManager::get()->requestObjectEvent(change, close, 0.0f);
        }
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjBlWeapon2::openCharChange() {
    if (m_openType == 0) {
        if (!GfMenuObjMainMenu2::isOpenCharMenu()) {
            return;
        }
        ui::UIObjectAcc chips(m_handle, "LAY_chips");
        GfMenuObjMainMenu2::openCharChange(chips.m_handle, 1, false);
    } else {
        ui::UIObjectAcc acc(m_handle);
        sendEvent(acc.searchChild("LAY_chr_change"), 0x21, 0);
    }
}

void GfMenuObjBlWeapon2::closeCharChange() {
    if (m_openType == 0) {
        if (!GfMenuObjMainMenu2::isOpenCharMenu()) {
            return;
        }
        ui::UIObjectAcc chips(m_handle, "LAY_chips");
        GfMenuObjMainMenu2::disableCharChange();
    } else {
        ui::UIObjectAcc acc(m_handle);
        sendEvent(acc.searchChild("LAY_chr_change"), 0x102, 0);
    }
}

bool GfMenuObjBlWeapon2::seqStart() {
    GfMenuObjOperationInfo::setDisp(false);
    GfMenuObjMainMenu2::setCloseKeyEnable(false);
    m_seqStep = false;
    return true;
}

bool GfMenuObjBlWeapon2::seqSrcLeave() {
    ui::UIObjectAcc image(m_handle, "LAY_wpn_img@01");
    if (!m_seqStep) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_zoom_2";
        param.m_motion = "fade_out";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
        ui::UIObjectAcc main(m_handle, "LAY_main");
        param = GfMenuObjUtil::CtrlParam();
        param.m_methods = 2;
        param.m_time = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_zoom_2", "fade_out");
        GfMenuObjUtil::startCtrl(main.m_handle, param, "LAY_bl_weapon@02");
        GfMenuObjUtil::startCtrl(main.m_handle, param, "IMG_weapon_arrow");
        m_seqStep = true;
        return false;
    }
    int ctrl = GfMenuObjUtil::getCtrlID(image.m_handle);
    if (ctrl != -1 && GfMenuObjUtil::isBusyCtrl(ctrl)) {
        return false;
    }
    m_seqStep = false;
    m_seq.addWait(15);
    m_seq.addJob(&GfMenuObjBlWeapon2::seqSrcAppear);
    return true;
}

void GfMenuObjBlWeapon2::WeaponListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        GfMenuWeaponAdapter::ReferenceChip chip;
        chip.m_reference = 0;
        chip.m_chip = m_owner->m_chip;
        setupWeapon(acc, m_owner->m_items, chip);
        if (m_owner->m_items->getSize() == 0) {
            acc.setDispChild(false, "LAY_wpn_img@02");
        }
    } else if (event.m_type == 0x21) {
        GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_bl_weapon@01"), 0, 2);
        GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_bl_weapon@02"), 0, 1);
    } else if (event.m_type == 0x22) {
        GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_bl_weapon@01"), 0, 2);
        GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_bl_weapon@02"), 0, 1);
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

void GfMenuObjBlWeapon2::setupWeapon(ui::UIObjectAcc& acc, GfMenuItemList* items,
                                     GfMenuWeaponAdapter::ReferenceChip& chip) {
    GfMenuWeaponAdapter* name =
        GfMenuWeaponAdapter::createFromReferenceBlade(acc.searchChild("TXT_wpname_@01"), 0, 0, false);
    if (name != nullptr) {
        name->m_rowHandle = acc.searchChild("LAY_bl_weapon_text@01");
    }
    GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_wpn_img@01"), 0x59, 0, true);
    GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_wpn_img_eff@01"), 0x59, 0, true);
    GfMenuObjUtil::setChildDisp(acc.m_handle, "TXT_wptype_@01", false);
    GfMenuWeaponAdapter::createFromReferenceBlade(acc.searchChild("TXT_wp_text_@01"), 6, 0, false);
    GfMenuObjUtil::createSyncPlugin(acc.searchChild("TXT_wp_text_no_eff@01"), acc.searchChild("TXT_wp_text_@01"), 0x40);

    name = GfMenuWeaponAdapter::createFromReferenceChip(acc.searchChild("TXT_wpname_@02"), 0, chip, false);
    if (name != nullptr) {
        name->m_rowHandle = acc.searchChild("LAY_bl_weapon_text@02");
    }
    GfMenuCharDataAdapter* image =
        GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_wpn_img@02"), 0x59, 0, true);
    if (image != nullptr) {
        image->m_virtualMode = 1;
    }
    GfMenuObjUtil::setChildDisp(acc.m_handle, "TXT_wp_chip_@02", false);
    GfMenuObjUtil::setChildDisp(acc.m_handle, "TXT_wptype_@02", false);
    GfMenuObjUtil::setChildDisp(acc.m_handle, "TXT_wp_plus_@02", false);
    GfMenuWeaponAdapter::createFromReferenceChip(acc.searchChild("TXT_wp_text_@02"), 6, chip, false);
    GfMenuObjUtil::createSyncPlugin(acc.searchChild("TXT_wp_text_no_eff@02"), acc.searchChild("TXT_wp_text_@02"), 0x40);
}

bool GfMenuObjBlWeapon2::seqEnd() {
    GfMenuObjOperationInfo::setDisp(true);
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    {
        ui::UIObjectAcc chips(m_handle, "LAY_chips");
        ui::EventData event;
        event.m_type = 0x100;
        GfMenuObject::sendEvent(chips.m_handle, event, 0.0f);
    }
    openCharChange();
    m_seqStep = false;
    return true;
}

bool GfMenuObjBlWeapon2::seqSrcAppear() {
    ui::UIObjectAcc image(m_handle, "LAY_wpn_img@01");
    if (!m_seqStep) {
        GfEquipUtil::equipBladeChip(GfMenuReference::getReferenceBladeID(0), m_chip->m_value);
        GfMenuObjUtil::playSE(0x12);
        MenuItemInfo item = m_items->getContents(m_items->getIndex(false));
        item.m_count = 1;
        unsigned int index = m_items->getIndex(false);
        m_items->decItem(item, false);
        if (m_openType == 1) {
            GfMenuItemList::ItemShopSetup setup;
            setup.m_setup.m_pageRowSize = m_select->getSize();
            setup.m_shop = m_shop;
            m_items->setupFromShop(setup);
            m_items->setIndex(index);
        }
        {
            ui::UIObjectAcc chips(m_handle, "LAY_chips");
            mm::mtl::FixStr<32> name;
            for (unsigned int i = 0; i < m_select->getSize();) {
                i++;
                name.format("IMG_ch_listcrsor_@%02d", i);
                chips.setDispChild(false, name.m_str);
            }
            GfMenuObject::resetInputSelection(chips.m_handle);
            GfMenuObject::setupInputSelectionFromList(chips.m_handle, *m_items);
        }
        m_chip->m_value = 0;
        image.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "sample";
        param.m_motion = "fadein";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
        m_seqStep = true;
        return false;
    }
    int ctrl = GfMenuObjUtil::getCtrlID(image.m_handle);
    if (ctrl != -1 && GfMenuObjUtil::isBusyCtrl(ctrl)) {
        return false;
    }
    m_seqStep = false;
    m_seq.addJob(&GfMenuObjBlWeapon2::seqSrcEffect);
    return true;
}

bool GfMenuObjBlWeapon2::seqSrcEffect() {
    ui::UIObjectAcc tag(m_handle, "IMG_wpn_tag_eff@01");
    if (!m_seqStep) {
        ui::UIObjectAcc image(m_handle, "IMG_wpn_img_eff@01");
        tag.startAnimationFromIndex(1, false);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "mnu071_wep_flash";
        param.m_motion = "flash";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
        m_seqStep = true;
        return false;
    }
    if (tag.isPlayingAnimation()) {
        return false;
    }
    {
        ui::UIObjectAcc weapon(m_handle, "LAY_bl_weapon@02");
        weapon.setDisp(true);
        int& chip = m_chip->m_value;
        chip = m_items->getContents(m_items->getIndex(false)).m_id;
        GfMenuReference::setBladeVirtualEquipWpnChip(m_items->getContents(m_items->getIndex(false)).m_id);
        if (m_items->getSize() == 0) {
            weapon.setDispChild(false, "LAY_wpn_img@02");
        }
    }
    m_seqStep = false;
    m_seq.addJob(&GfMenuObjBlWeapon2::seqDstResume);
    return true;
}

bool GfMenuObjBlWeapon2::seqDstResume() {
    ui::UIObjectAcc weapon(m_handle, "LAY_bl_weapon@02");
    if (!m_seqStep) {
        ui::UIObjectAcc arrow(m_handle, "IMG_weapon_arrow");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = 0.25f;
        GfMenuObjUtil::startCtrl(weapon.m_handle, param, nullptr);
        GfMenuObjUtil::startCtrl(arrow.m_handle, param, nullptr);
        m_seqStep = true;
        return false;
    }
    int ctrl = GfMenuObjUtil::getCtrlID(weapon.m_handle);
    if (ctrl != -1 && GfMenuObjUtil::isBusyCtrl(ctrl)) {
        return false;
    }
    m_seqStep = false;
    m_seq.addJob(&GfMenuObjBlWeapon2::seqEnd);
    return true;
}

void GfMenuObjBlWeapon2::openForShop(unsigned int shop) {
    GfMenuTypes::Param param;
    param.m_halves.m_param = shop;
    param.m_halves.m_type = 1;
    GfMenuFullScreen::registLayerParam(GfMenuObject::getMenuLayerID(0x21), param);
    ui::UIManager::get()->createLayer(0x2D);
}

bool GfMenuObjBlWeapon2::attach(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x68));
    bool attached = false;
    if (acc.m_object != nullptr) {
        GfMenuObject::startCallContext(context, 0x68, acc.m_handle);
        attached = true;
    }
    return attached;
}

}  // namespace gf

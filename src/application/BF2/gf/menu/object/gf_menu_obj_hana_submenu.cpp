#include "ui/EventData.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjHanaSubmenu.h"
#include "classes/gf/GfMenuObjHanaSubmenu/MainListener.h"
#include "classes/gf/GfMenuObjHanaSubmenu/SubmenuListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectDockPlugin.h"
#include "mm/Vec2.h"
#include "mm/mtl/FixStr.h"

namespace gf {

namespace {
// what each submenu entry opens: the menu (its full-screen layer) and the menu condition that has to be met (the
// names are not the original's)
struct SubmenuEntry {
    unsigned int m_menu;
    unsigned int m_condition;
};
const SubmenuEntry s_entries[] = {
    {0x2E, 0x12},
    {0x2F, 0x13},
    {0x30, 0x14},
};
}  // namespace

GfMenuObjHanaSubmenu::GfMenuObjHanaSubmenu(unsigned int handle)
    : GfMenuObject(handle), m_cursor(nullptr), m_select(0) {}

GfMenuObjHanaSubmenu::~GfMenuObjHanaSubmenu() {
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
}

void GfMenuObjHanaSubmenu::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 101
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x71, main);
    unsigned int submenu = acc.searchChild("LAY_sub_menu");
#line 107
    SubmenuListener* submenuListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SubmenuListener(this);
    submenuListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(submenu, submenuListener);
    if (submenuListener != nullptr) {
        submenuListener->release();
    }
    GfMenuObject::initialize();
}

void GfMenuObjHanaSubmenu::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjHanaSubmenu::update() {
    GfMenuObject::update();
}

void GfMenuObjHanaSubmenu::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObjOperationInfo::add(acc.searchChild("LAY_sub_menu"), 0, 0, 0);
        GfMenuObjOperationInfo::setGuideText(10, 0);
        setFadeIn(handle);
        break;
    case 3:
        if (event.m_param0 == 2) {
            GfMenuObjOperationInfo::remove(acc.searchChild("LAY_sub_menu"), 0, 0, 0);
            acc.setDisp(false);
            acc.setTerm();
            GfMenuObjCharSelect::returnSubMenu();
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        setFadeOut(handle);
        break;
    case 0x101:
        GfMenuObjOperationInfo::add(acc.searchChild("LAY_sub_menu"), 0, 0, 0);
        GfMenuObjOperationInfo::setGuideText(10, 0);
        GfMenuObjCharSelect::dispOnChar(1);
        sendEvent(acc.searchChild("LAY_sub_menu"), 0x102, 0);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjHanaSubmenu::SubmenuListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        setupSubmenu(acc);
        GfMenuObjUtil::CursorParam param;
        param.m_parent = ui::UIObjectAcc(handle).getParentHandle();
        param.m_cursor = owner.searchChild("IMG_sub_cursor");
        param.m_type = 0;
        param.m_setting.m_dockType = 0;
        param.m_pickup = "LAY_sub_menu_bl@%02d";
        m_owner->m_cursor = GfMenuObjUtil::createCursor(param);
        m_owner->m_cursor->open(0);
        ui::UIObjectAcc icon(acc.searchChild("IMG_sub_menu_bl_icon@01"));
        mm::Vec2 scale;
        icon.getScale(scale);
        m_owner->m_iconScale = scale.x;
        m_owner->m_iconSelectScale = scale.x * 1.5f;
        GfMenuObject::setupInputSelection(handle, 0, 3);
        GfMenuObject::enableInput(handle);
        break;
    }
    case 6: {
        int index = event.m_param0;
        int last = event.m_param1;
        m_owner->m_cursor->inputChange(index);
        mm::mtl::FixStr<32> bg;
        mm::mtl::FixStr<32> lastBg;
        mm::mtl::FixStr<32> icon;
        mm::mtl::FixStr<32> lastIcon;
        bg.format("IMG_sub_menu_bl_bg@%02d", index + 1);
        lastBg.format("IMG_sub_menu_bl_bg@%02d", last + 1);
        icon.format("IMG_sub_menu_bl_icon@%02d", index + 1);
        lastIcon.format("IMG_sub_menu_bl_icon@%02d", last + 1);
        if (index >= 0) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x80000;
            param.m_curve = 0;
            param.m_time = 0.2f;
            param.m_scale = m_owner->m_iconSelectScale;
            GfMenuObjUtil::startCtrl(acc.searchChild(icon.m_str), param, nullptr);
            ui::UIObjectAcc bgAcc(acc.searchChild(bg.m_str));
            bgAcc.startAnimation("sellect", false);
            m_owner->m_select = index;
        }
        if (last >= 0 && index != last) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x80000;
            param.m_curve = 0;
            param.m_time = 0.2f;
            param.m_scale = m_owner->m_iconScale;
            GfMenuObjUtil::startCtrl(acc.searchChild(lastIcon.m_str), param, nullptr);
            ui::UIObjectAcc bgAcc(acc.searchChild(lastBg.m_str));
            bgAcc.startAnimation("idol", false);
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            unsigned int select = m_owner->m_select;
            if (GfMenuObjUtil::getMenuCondition(s_entries[select].m_condition)) {
                GfMenuObjOperationInfo::remove(owner.searchChild("LAY_sub_menu"), 0, 0, 0);
                sendEvent(handle, 0x103, 0);
                if (m_owner->m_select < 3) {
                    GfMenuObjCharSelect::dispOffChar(1);
                    GfMenuObject::changeFSSubLayer(owner.m_handle, 3,
                                                   GfMenuObject::getMenuLayerID(s_entries[select].m_menu), true);
                }
            }
        } else if (event.m_param1 == 2) {
            sendEvent(owner.searchChild("LAY_main"), 0x22, 0);
            GfMenuObject::disableInput(handle);
        }
        break;
    case 0x102:
        acc.setDisp(true);
        GfMenuObject::enableInput(handle);
        break;
    case 0x103:
        acc.setDisp(false);
        GfMenuObject::disableInput(handle);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjHanaSubmenu::setupSubmenu(ui::UIObjectAcc& acc) {
    GfDataBdat::getFP(0x119);
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 3; i++) {
        name.format("IMG_sub_menu_bl_icon@%02d", i + 1);
        ui::UIObjectAcc icon(acc.searchChild(name.m_str));
        icon.setImageIndex(i);
        name.format("LAY_sub_menu_bl_text@%02d", i + 1);
        ui::UIObjectDockPlugin* dock = ui::UIObjectDockPlugin::create(acc.searchChild(name.m_str), 0, 0, icon.m_handle);
        dock->m_side = 1;
        if (dock != nullptr) {
            dock->release();
        }
    }
}

void GfMenuObjHanaSubmenu::returnHanaSubMenu() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x71);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x101;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

}  // namespace gf

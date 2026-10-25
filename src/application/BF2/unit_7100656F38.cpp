// The ocMenu script class (a monolib VM OC plugin on gf::GfMenuScriptManager's menus): its methods, constructor
// function, class table and Regist function. The methods are static and nothing names them: they keep placeholder
// fn_ names.
#include "vm/yvm2.h"
#include "classes/gf/GfMenuScriptManager.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UICtrlManager.h"
#include "classes/ui/UILayoutObject.h"
#include "ui/EventData.h"
#include "ui/UIUtil.h"

// ocMenu(id): the menu script manager's handle for that id
static int fn_7100656ED4(VMThread* th, void* unused, unsigned long ocId) {
    int id = vmArgIntGet(1, vmArgPtrGet(th, 1));
    unsigned int handle = gf::GfMenuScriptManager::getHandle(id);
    VMData ret;
    ret.type = VMDATA_OC;
    ret.hi = ocId;
    ret.v.obj = reinterpret_cast<void*>(static_cast<unsigned long>(handle));
    vmRetValSet(th, &ret);
    return 1;
}

// ocMenu.checkEvent(): whether the menu has an event waiting
static int fn_7100656F38(VMThread* th, unsigned long handle) {
    VMData ret;
    ret.type = gf::GfMenuScriptManager::checkEvent(handle) ? VMDATA_TRUE : VMDATA_FALSE;
    vmRetValSet(th, &ret);
    return 1;
}

// ocMenu.getEventID(): the type of the event checkEvent took (0 without one)
static int fn_7100656F84(VMThread* th, unsigned long handle) {
    VMData ret;
    ui::EventData event(0);
    if (gf::GfMenuScriptManager::getEventData(handle, event)) {
        int type = event.m_type;
        ret.type = VMDATA_INT;
        ret.v.i = type;
    } else {
        ret.type = VMDATA_INT;
        ret.v.i = 0;
    }
    vmRetValSet(th, &ret);
    return 1;
}

// ocMenu.getEventData(index): that parameter (0-3) of the event checkEvent took (0 without one)
static int fn_7100656FF4(VMThread* th, unsigned long handle) {
    int index = vmArgIntGet(1, vmArgPtrGet(th, 1));
    VMData ret;
    ui::EventData event(0);
    if (gf::GfMenuScriptManager::getEventData(handle, event)) {
        // the four int parameters read by index from the first (an int[4] view in the union compiles differently)
        int param = static_cast<unsigned int>(index) < 4 ? (&event.m_param0)[index] : 0;
        ret.type = VMDATA_INT;
        ret.v.i = param;
    } else {
        ret.type = VMDATA_INT;
        ret.v.i = 0;
    }
    vmRetValSet(th, &ret);
    return 1;
}

// ocMenu.setDisp(disp)
static int fn_710065709C(VMThread* th, unsigned long handle) {
    int disp = vmArgBoolGet(1, vmArgPtrGet(th, 1));
    ui::UIObjectAcc acc(handle);
    acc.setDisp(disp != 0);
    return 0;
}

// ocMenu.setText(child, id): the child's text from the menu's message id
static int fn_7100657100(VMThread* th, unsigned long handle) {
    const char* child = vmArgStringGet(1, vmArgPtrGet(th, 1));
    int id = vmArgIntGet(2, vmArgPtrGet(th, 2));
    ui::UIObjectAcc acc(handle);
    gf::GfMenuObject::setText(acc.searchChild(child), id);
    return 0;
}

// ocMenu.setImageIndex(child, index): shows the child with that image (-1: leaves it)
static int fn_7100657190(VMThread* th, unsigned long handle) {
    const char* child = vmArgStringGet(1, vmArgPtrGet(th, 1));
    int index = vmArgIntGet(2, vmArgPtrGet(th, 2));
    if (index != -1) {
        ui::UIObjectAcc acc(handle);
        ui::UIObjectAcc childAcc(acc.searchChild(child));
        if (childAcc.m_object != nullptr) {
            childAcc.setImageIndex(index);
            childAcc.setDisp(true);
        } else {
            childAcc.setDisp(false);
        }
    }
    return 0;
}

// ocMenu.fadeIn(): the menu's alpha from 0 to 1 over a second
static int fn_7100657260(VMThread* th, unsigned long handle) {
    ui::UIUtil::getLayoutObject(handle)->m_displayInfo.m_mulColor.a = 0.0f;
    int slot = ui::UICtrlManager::get()->reserveCtrlSlot(handle, false);
    if (slot != -1) {
        ui::UICtrlManager::get()->addAlphaMethod(slot, 1.0f, ui::CURVE_TYPE(0));
        ui::UICtrlManager::get()->startCtrl(slot, 1.0f, 1, 0);
    }
    return 0;
}

// ocMenu.fadeOut(): the menu's alpha to 0 over half a second
static int fn_71006572E8(VMThread* th, unsigned long handle) {
    int slot = ui::UICtrlManager::get()->reserveCtrlSlot(handle, false);
    if (slot != -1) {
        ui::UICtrlManager::get()->addAlphaMethod(slot, 0.0f, ui::CURVE_TYPE(0));
        ui::UICtrlManager::get()->startCtrl(slot, 0.5f, 1, 0);
    }
    return 0;
}

// ocMenu.startCtrl(time, flag = true): runs the control the add* calls set up
static int fn_7100657350(VMThread* th, unsigned long handle) {
    int flag = 1;
    float time = vmArgFixedGet(1, vmArgPtrGet(th, 1));
    if (vmArgOmitChk(th, 2) == 0) {
        flag = vmArgBoolGet(2, vmArgPtrGet(th, 2));
    }
    int slot = gf::GfMenuScriptManager::getCtrlId(handle);
    if (slot != -1) {
        ui::UICtrlManager::get()->startCtrl(slot, time, flag != 0, 0);
    }
    return 0;
}

// ocMenu.undoCtrl(time): back to the object's defaults over that time
static int fn_7100657404(VMThread* th, unsigned long handle) {
    float time = vmArgFixedGet(1, vmArgPtrGet(th, 1));
    int slot = gf::GfMenuScriptManager::getCtrlId(handle);
    if (slot != -1) {
        ui::UICtrlManager::get()->addUndoMethod(slot, ui::CURVE_TYPE(0));
        ui::UICtrlManager::get()->startCtrl(slot, time, 1, 0);
        gf::GfMenuScriptManager::setCtrlId(handle, -1);
    }
    return 0;
}

// ocMenu.addCtrlScale(x, y): a scale to that factor of the object's
static int fn_710065749C(VMThread* th, unsigned long handle) {
    float x = vmArgFixedGet(1, vmArgPtrGet(th, 1));
    float y = vmArgFixedGet(2, vmArgPtrGet(th, 2));
    int slot = gf::GfMenuScriptManager::getCtrlId(handle);
    if (slot == -1) {
        slot = ui::UICtrlManager::get()->reserveCtrlSlot(handle, false);
        gf::GfMenuScriptManager::setCtrlId(handle, slot);
        if (slot == -1) {
            return 0;
        }
    }
    ui::UIObject* object = ui::UIUtil::getObject(handle);
    ui::UICtrlManager::get()->addScaleMethod(slot, x * object->m_transform.m_scaleX, y * object->m_transform.m_scaleY,
                                             ui::CURVE_TYPE(1));
    return 0;
}

// ocMenu.addCtrlPosition(x, y): a move by that much from the object's position
static int fn_7100657570(VMThread* th, unsigned long handle) {
    int x = vmArgIntGet(1, vmArgPtrGet(th, 1));
    int y = vmArgIntGet(2, vmArgPtrGet(th, 2));
    int slot = gf::GfMenuScriptManager::getCtrlId(handle);
    if (slot == -1) {
        slot = ui::UICtrlManager::get()->reserveCtrlSlot(handle, false);
        gf::GfMenuScriptManager::setCtrlId(handle, slot);
        if (slot == -1) {
            return 0;
        }
    }
    ui::UIObject* object = ui::UIUtil::getObject(handle);
    mm::Pnt<short> pos(object->m_transform.m_pos);
    ui::UICtrlManager::get()->addPositionMethod(slot, pos.x + x, pos.y + y, ui::CURVE_TYPE(1));
    return 0;
}
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B72B00).
static VMOCMethod s_ocMenuMethods[] = {
    {"checkEvent", reinterpret_cast<void*>(&fn_7100656F38), 0},
    {"getEventID", reinterpret_cast<void*>(&fn_7100656F84), 0},
    {"getEventData", reinterpret_cast<void*>(&fn_7100656FF4), 0},
    {"setDisp", reinterpret_cast<void*>(&fn_710065709C), 0},
    {"setText", reinterpret_cast<void*>(&fn_7100657100), 0},
    {"setImageIndex", reinterpret_cast<void*>(&fn_7100657190), 0},
    {"fadeIn", reinterpret_cast<void*>(&fn_7100657260), 0},
    {"fadeOut", reinterpret_cast<void*>(&fn_71006572E8), 0},
    {"startCtrl", reinterpret_cast<void*>(&fn_7100657350), 0},
    {"undoCtrl", reinterpret_cast<void*>(&fn_7100657404), 0},
    {"addCtrlScale", reinterpret_cast<void*>(&fn_710065749C), 0},
    {"addCtrlPosition", reinterpret_cast<void*>(&fn_7100657570), 0},
    {nullptr, nullptr, 0},
};

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B72AE0).
static VMOC s_ocMenu = {"ocMenu", reinterpret_cast<void*>(&fn_7100656ED4), nullptr, s_ocMenuMethods};

void ocMenuRegist() {
    vmOCRegist(&s_ocMenu);
}

// The original has ocMenu (from 0x7100656EC8) and pluginRegist (0x7100657648) as their own translation units
// (session 19 vmplug2/SPLITS.md); they share this file until the split is fixed.
// Registers every script VM plugin and script class, in the original's order.
#include "plugin/PluginRegist.h"

void pluginRegist() {
    ocBuiltinRegist();
    ocThreadRegist();
    ocBdatRegist();
    ocMenuRegist();
    ocAiDataRegist();
    pluginWaitRegist();
    pluginDebRegist();
    pluginSysRegist();
    pluginFldRegist();
    pluginPartyRegist();
    pluginUiRegist();
    pluginEvtRegist();
    pluginEvtObjRegist();
    pluginEvtSetupRegist();
    pluginEvtCharaRegist();
    pluginEvtCamRegist();
    pluginEvtEffRegist();
    pluginEvtLgtRegist();
    pluginEvtPostRegist();
    pluginEvtTextRegist();
    pluginEvtSelRegist();
    pluginEvtStatusRegist();
    pluginEvtBgmRegist();
    pluginEvtSeRegist();
    pluginEvtVolRegist();
    pluginEvtRandRegist();
    pluginEvtPayRegist();
    fn_710066162C();
    pluginEvtEnvRegist();
    pluginEvtMovRegist();
    pluginEvtMapRegist();
    pluginEvtUiRegist();
    pluginEvtVoiceRegist();
    pluginBtlAiRegist();
    pluginGmkRegist();
}

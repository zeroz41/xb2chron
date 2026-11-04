#include "classes/gf/GfMenuObjPartyStatus.h"
#include "classes/gf/GfMenuObjPartyStatus/MainListener.h"
#include "classes/gf/GfMenuObjPartyStatus/ComboReqListener.h"
#include "classes/gf/GfMenuObjPartyStatus2.h"
#include "classes/gf/GfMenuObjPartyStatus.h"
#include "classes/gf/GfMenuObjPartyStatus/MainListener.h"
#include "classes/gf/GfMenuObjPartyStatus/ComboReqListener.h"
#include "classes/gf/GfMenuObjPartyStatus2.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataParty.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfGameParty.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjPartyStatus::GfMenuObjPartyStatus(unsigned int handle) : GfMenuObject(handle) {
    m_locked = false;
    m_effectCtrl[2] = -1;
    m_effectCtrl[0] = -1;
    m_effectCtrl[1] = -1;
}

GfMenuObjPartyStatus::~GfMenuObjPartyStatus() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjPartyStatus::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (acc.m_object != nullptr) {
#line 103
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0x3D, acc.m_handle);
        {
            ui::UIObjectAcc combo(m_handle, "LAY_combo_req2");
            if (combo.m_object != nullptr) {
                GfMenuObject::attachExternalCall(0x3E, combo.m_handle);
#line 117
                ComboReqListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ComboReqListener(this);
                listener->m_RefCount = 1;
                ui::UIEventManager::get()->registObjectListener(combo.m_handle, listener);
                if (listener != nullptr) {
                    listener->release();
                }
            }
            GfMenuObjUtil::createDockPlugin(combo.searchChild("IMG_combo_req2_name_top@01"),
                                            combo.searchChild("IMG_combo_req2_name_base@01"), 1, mm::Pnt<short>(0, 0), 0);
            GfMenuObjUtil::createDockPlugin(combo.searchChild("IMG_combo_req2_name_top@02"),
                                            combo.searchChild("IMG_combo_req2_name_base@02"), 1, mm::Pnt<short>(0, 0), 0);
            GfMenuObjUtil::createDockPlugin(combo.searchChild("IMG_combo_req2_name_top@03"),
                                            combo.searchChild("IMG_combo_req2_name_base@03"), 0, mm::Pnt<short>(0, 0), 0);
        }
        mm::mtl::FixStr<32> name;
        for (int i = 0; i < 3; i++) {
            name.format("IMG_mem%d_hpgauge", i + 1);
            GfMenuGfObjAdapter::createFromPartyDriver(acc.searchChild(name.m_str), 0, i, true);
            ui::UIObjectAcc(acc.searchChild(name.m_str)).setExtType(1);
            GfMenuObject::addNumberEventCondition(acc.m_handle, name.m_str, 0x1000, i + 1, 1.0f);
            GfMenuObject::addNumberEventCondition(acc.m_handle, name.m_str, 0x1001, i + 1, 0.2f);
            GfMenuObject::addNumberEventCondition(acc.m_handle, name.m_str, 0x1002, i + 1, 0.0f);
        }
        GfMenuObject::initialize();
    }
}

void GfMenuObjPartyStatus::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjPartyStatus::update() {
    GfMenuObject::update();
}

int GfMenuObjPartyStatus::openPartyStatus(unsigned int handle, int value) {
    unsigned int id = GfMenuObjUtil::getLeaderPartyID();
    ui::UIObjectAcc acc(handle);
    if (id == static_cast<unsigned int>(-1)) {
        value = -1;
    } else {
        for (int i = 0; i < 3; i++) {
            mm::mtl::FixStr<32> name;
            name.format("LAY_mem%d", i + 1);
            if (id == GfMenuObjUtil::getLeaderPartyID() ||
                GfGameParty::getHandleDriver(id, static_cast<PTPOS>(0)) != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                acc.setDispChild(true, name.m_str);
            } else {
                acc.setDispChild(false, name.m_str);
            }
            if (++id >= 3) {
                id = 0;
            }
        }
        {
            ui::UIObjectAcc combo(m_handle, "LAY_combo_req2");
            if (combo.m_object != nullptr) {
                ui::EventData event;
                event.m_type = 0x21;
                ui::UIManager::get()->requestObjectEvent(combo.m_handle, event, 0.0f);
            }
        }
        GfMenuObjPartyStatus2::open();
    }
    return value;
}

void GfMenuObjPartyStatus::closePartyStatus(unsigned int handle, int value) {
    ui::UIObjectAcc acc(handle);
    {
        ui::UIObjectAcc combo(m_handle, "LAY_combo_req2");
        if (combo.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x22;
            ui::UIManager::get()->requestObjectEvent(combo.m_handle, event, 0.0f);
        }
    }
    GfMenuObjPartyStatus2::close();
}

void GfMenuObjPartyStatus::setupComboReq(const ui::UIObjectAcc& acc, unsigned short index, unsigned short combo,
                                         bool showButton, unsigned short effect, unsigned int button) {
    // the default button of each request slot (the name is not the original's)
    static const unsigned int s_buttons[3] = {4, 0x40, 0x80};
    mm::mtl::FixStr<32> name;
    mm::mtl::FixStr<32> color;
    unsigned char atr = GfMenuObjUtil::getElementComboAtr(combo);
    color.format("elemental%02d", atr);
    name.format("TXT_combo_req2_name@%02d", index + 1);
    ui::UIObjectAcc text(acc.m_handle, name.m_str);
    if (text.m_object != nullptr) {
        text.setText(GfMenuObjUtil::getElementComboName(combo));
        mm::mtl::FixStr<32> face;
        face.format("element%02d", atr);
        text.setTextFacePattern(face.m_str);
    }
    name.format("IMG_combo_req2_name_bg@%02d", index + 1);
    ui::UIObjectAcc(acc.m_handle, name.m_str).setMulColor(color.m_str);
    name.format("IMG_combo_req2_name_base@%02d", index + 1);
    ui::UIObjectAcc(acc.m_handle, name.m_str).setMulColor(color.m_str);
    name.format("IMG_combo_req2_name_top@%02d", index + 1);
    ui::UIObjectAcc(acc.m_handle, name.m_str).setMulColor(color.m_str);
    name.format("IMG_combo_req2_btn_bg@%02d", index + 1);
    ui::UIObjectAcc(acc.m_handle, name.m_str).setMulColor(color.m_str);
    name.format("IMG_combo_req2_btn_disable@%02d", index + 1);
    ui::UIObjectAcc disable(acc.m_handle, name.m_str);
    if (disable.m_object != nullptr) {
        disable.setDisp(false);
    }
    name.format("IMG_combo_req2_btn@%02d", index + 1);
    ui::UIObjectAcc btn(acc.m_handle, name.m_str);
    if (btn.m_object != nullptr) {
        btn.setDisp(showButton);
    }
    name.format("IMG_combo_req2_eff@%02d", index + 1);
    ui::UIObjectAcc eff(acc.m_handle, name.m_str);
    if (effect != 0) {
        eff.setImageIndex(effect - 1);
        eff.setAlpha(1.0f);
    } else {
        eff.setAlpha(0.0f);
    }
    if (button == 0) {
        button = s_buttons[index];
    }
    name.format("IMG_combo_req2_btn@%02d", index + 1);
    int icon = GfMenuObjUtil::getBtnIconNumber(button);
    ui::UIObjectAcc(acc.m_handle, name.m_str).setImageIndex(GfMenuBdat::getIconImageIndex(icon));
    if (index == 0) {
        bool sp = false;
        if (GfDataParty::getDriver(index, static_cast<PTPOS>(0)) == 1) {
            sp = GfDataDriver::getBlade(1, -1) == 0x3EB;
        }
        ui::UIObjectAcc(acc.m_handle, "IMG_combo_req2_sp@01").setDisp(sp);
    }
}

void GfMenuObjPartyStatus::open(bool flag) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3D));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = flag;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjPartyStatus::close(bool flag) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3D));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x22;
        event.m_param0 = flag;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjPartyStatus::lock(bool lock) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3D));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x110;
        event.m_param0 = lock;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjPartyStatus::attachComboRequest(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3E));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        GfMenuObject::startCallContext(context, 0x3E, acc.m_handle);
    }
}

void GfMenuObjPartyStatus::openComboRequest(unsigned short index, const RequestParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3E));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x101;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = param.m_combo;
        event.m_paramShort[2] = param.m_showButton;
        event.m_paramShort[3] = param.m_effect;
        event.m_param2 = param.m_button;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjPartyStatus::closeComboRequest(unsigned short index, bool flag) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3E));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x102;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = flag;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjPartyStatus::resetComboRequest(unsigned short index, const RequestParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3E));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x103;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = param.m_combo;
        event.m_paramShort[2] = param.m_showButton;
        event.m_paramShort[3] = param.m_effect;
        event.m_param2 = param.m_button;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjPartyStatus::memberChange(unsigned short member, unsigned int value) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3D));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x109;
        event.m_param0 = member;
        event.m_param1 = value;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

}  // namespace gf

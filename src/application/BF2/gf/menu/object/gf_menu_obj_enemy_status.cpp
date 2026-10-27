#include "classes/gf/GfMenuObjEnemyStatus.h"
#include "classes/gf/GfMenuObjEnemyStatus/MainListener.h"
#include "classes/gf/GfMenuObjEnemyStatus/ElemListener.h"
#include "classes/gf/GfMenuObjEnemyStatus.h"
#include "classes/gf/GfMenuObjEnemyStatus/MainListener.h"
#include "classes/gf/GfMenuObjEnemyStatus/ElemListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfObjAcc.h"
#include "mm/mtl/FixStr.h"
#include "mm/Rect.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjEnemyStatus::GfMenuObjEnemyStatus(unsigned int handle)
    : GfMenuObject(handle), m_target(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_adapters(), m_suspendCtrl(-1),
      m_seq(this) {}

GfMenuObjEnemyStatus::~GfMenuObjEnemyStatus() {}

void GfMenuObjEnemyStatus::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjEnemyStatus::update() {
    GF_OBJ_HANDLE* target = GfMenuManager::getTargetObjHandle();
    if (m_target != target) {
        for (unsigned int i = 0; i < m_adapters.m_list.size(); i++) {
            m_adapters.m_list[i]->changeGfObj(target);
        }
        {
            ui::UIObjectAcc acc(m_handle, "LAY_main");
            GfObjAcc obj(m_target);
            ui::EventData event;
            event.m_type = 0x10A;
            event.m_param0 = m_target == reinterpret_cast<GF_OBJ_HANDLE*>(-1) ? true : obj.getType() != 5;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
        m_target = target;
    }
    m_seq.update();
    if (GfMenuObjUtil::fn_710048FD30(1)) {
        bool battle = GfMenuManager::isBattleState(8);
        ui::UIObjectAcc acc(m_handle, "LAY_arts_name");
        acc.setAlpha(battle ? 0.0f : 1.0f);
    }
    GfMenuObject::update();
}

void GfMenuObjEnemyStatus::fn_71003F98A4(unsigned int layout, unsigned int handle, int index) {
    ui::UIObjectAcc acc(layout);
    ui::UIObjectAcc obj(handle);
    if (acc.m_object != nullptr && obj.m_object != nullptr) {
        mm::mtl::FixStr<16> name;
        name.format("elem_%02d", index);
        mm::Rect<short> rect;
        if (acc.getLayoutRect(name.m_str, rect)) {
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 0.25f;
            param.m_methods = 0x80;
            param.m_curve = 1;
            param.m_pos[0] = rect.x;
            param.m_pos[1] = rect.y;
            GfMenuObjUtil::startCtrl(obj.m_handle, param, nullptr);
        }
    }
}

void GfMenuObjEnemyStatus::ElemListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0xD: {
            int value = event.m_param0;
            if (event.m_param1 == 1) {
                if (value == 5) {
                    acc.setAddColor("white");
                    GfMenuObjUtil::CtrlParam param;
                    param.m_methods = 0x4000000;
                    param.m_time = 0.5f;
                    param.m_color = GfMenuObjUtil::getPresetColor("black");
                    GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
                }
            } else if (event.m_param1 == 2) {
                ui::UIObjectAcc suspend(acc.m_handle, "LAY_elem_time_suspend");
                if (value == 5) {
                    suspend.setDisp(true);
                    suspend.setAlpha(0.0f);
                    GfMenuObjUtil::CtrlParam param;
                    param.m_methods = 4;
                    param.m_time = 0.5f;
                    param.m_alpha = 1.0f;
                    param.m_reserve = true;
                    param.m_curve = 3;
                    m_owner->m_suspendCtrl = GfMenuObjUtil::startCtrl(suspend.m_handle, param, nullptr);
                } else if (m_owner->m_suspendCtrl != -1) {
                    GfMenuObjUtil::stopCtrl(m_owner->m_suspendCtrl);
                    m_owner->m_suspendCtrl = -1;
                    suspend.setDisp(false);
                }
            }
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjEnemyStatus::open(const OpenParam& param) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x10);
    bool exists = ui::UIObjectAcc(handle).m_object != nullptr;
    if (exists) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (!term) {
            ui::EventData event;
            event.m_type = 0x100;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjEnemyStatus::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x10);
    bool exists = ui::UIObjectAcc(handle).m_object != nullptr;
    if (exists) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (!term) {
            ui::EventData event;
            event.m_type = 0x101;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjEnemyStatus::disp(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x14));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        acc.setDisp(disp);
    }
}

}  // namespace gf

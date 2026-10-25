#include "classes/ui/UITransform.h"
#include "classes/ui/UICtrlMethodAlpha.h"
#include "classes/ui/UICtrlMethodBright.h"
#include "classes/ui/UICtrlMethodPos.h"
#include "classes/ui/UICtrlMethodScale.h"
#include "classes/ui/UICtrlMethodRot.h"
#include "classes/ui/UICtrlMethodMulColor.h"
#include "classes/ui/UICtrlMethodAddColor.h"
#include "classes/ui/UICtrlMethodMotion.h"
#include "classes/ui/UIMotionData.h"
#include "classes/ui/UICtrlManager.h"
#include "classes/ui/UICtrlManager.h"
#include "classes/ui/IUICtrlUpdater.h"
#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIMotionData.h"
#include "classes/ui/UIMotionLibrary.h"
#include "classes/ui/UIObject.h"
#include "ui/UIUtil.h"

namespace ui {

UICtrlManager::UICtrlManager() : m_slots() {
    for (int i = 0; i < 128; i++) {
        m_slots[i].m_object = nullptr;
        m_slots[i].m_handle = 0;
        m_slots[i].m_eventHandle = 0;
        m_slots[i].m_ctrl.stop();
    }
}

UICtrlManager::~UICtrlManager() {
    for (mm::mtl::IntrusiveList<UICtrlObject>::iterator it = m_ctrlObjects.begin(); it != m_ctrlObjects.end();) {
        UICtrlObject* object = it.operator->();
        it = m_ctrlObjects.erase(it);
        if (object != nullptr) {
            object->release();
        }
    }
    m_ctrlObjects.clear();
    for (int i = 0; i < 128; i++) {
        if (m_slots[i].m_object != nullptr) {
            m_slots[i].m_object->release();
            m_slots[i].m_object = nullptr;
        }
    }
}

void UICtrlManager::releaseCtrlSlot(int slot) {
    if (m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_object->m_flags &= ~1;
        if (m_slots[slot].m_flags & 2) {
            m_slots[slot].m_object->setTerm();
        }
        m_slots[slot].m_ctrl.stop();
        if (m_slots[slot].m_object != nullptr) {
            m_slots[slot].m_object->release();
            m_slots[slot].m_object = nullptr;
        }
        m_slots[slot].m_handle = 0;
        m_slots[slot].m_eventHandle = 0;
    }
}

void UICtrlManager::setDefault(int slot) {
    if (slot >= 0 && slot <= 128u && m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_object->m_transform = m_slots[slot].m_defTransform;
        m_slots[slot].m_object->m_displayInfo = m_slots[slot].m_defDisplayInfo;
    }
}

void UICtrlManager::stopCtrl(int slot, bool release, bool notify) {
    m_slots[slot].m_ctrl.stop();
    if (notify && m_slots[slot].m_eventHandle != 0) {
        UIObject* object = UIUtil::getObject(m_slots[slot].m_eventHandle);
        if (object != nullptr && (object->m_flags & 2) != 0) {
            UIEventManager::EventInfo event;
            event.m_handle = m_slots[slot].m_eventHandle;
            event.m_data.m_type = 3;
            UIEventManager::get()->pushObjectEvent(event);
        }
    }
    if (m_slots[slot].m_flags & 8) {
        setDefault(slot);
    }
    if (release) {
        releaseCtrlSlot(slot);
    }
}

int UICtrlManager::reserveCtrlSlot(unsigned int handle, bool loop) {
    if (!UIUtil::isValid(handle)) {
        return -1;
    }
    for (unsigned int i = 0; i < 128; i++) {
        if (m_slots[i].m_handle == handle) {
            m_slots[i].m_loop = loop;
            return i;
        }
    }
    int slot = -1;
    for (unsigned int i = 0; i < 128; i++) {
        if (m_slots[i].m_object == nullptr) {
            slot = i;
            m_slots[i].m_handle = handle;
            m_slots[i].m_eventHandle = handle;
            m_slots[i].m_object = UIUtil::getObject(handle);
            m_slots[i].m_object->addRef();
            m_slots[i].m_methods.clear();
            m_slots[i].m_delayTime = 0.0f;
            m_slots[i].m_loop = loop;
            m_slots[i].m_flags = 0;
            m_slots[i].m_defTransform = m_slots[i].m_object->m_transform;
            m_slots[i].m_defDisplayInfo = m_slots[i].m_object->m_displayInfo;
            break;
        }
    }
    return slot;
}

int UICtrlManager::getCtrlSlot(unsigned int handle) {
    for (unsigned int i = 0; i < 128; i++) {
        if (m_slots[i].m_handle == handle) {
            return i;
        }
    }
    return -1;
}

void UICtrlManager::changeEventHandleObject(int slot, unsigned int handle) {
    if (slot != -1 && m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_eventHandle = handle;
    }
}

void UICtrlManager::setDelayTime(int slot, float time) {
    if (m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_delayTime = time;
    }
}

void UICtrlManager::addPositionMethod(int slot, short x, short y, CURVE_TYPE curve) {
    if (m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_pos.setup(m_slots[slot].m_object, mm::Pnt<short>(x, y));
        UICtrl::Method method;
        method.m_method = &m_slots[slot].m_pos;
        method.m_curve = UIUtil::getCurve(curve);
        m_slots[slot].m_methods.push_back(method);
    }
}

void UICtrlManager::addScaleMethod(int slot, float x, float y, CURVE_TYPE curve) {
    if (m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_scale.setup(m_slots[slot].m_object, mm::Vec2(x, y));
        UICtrl::Method method;
        method.m_method = &m_slots[slot].m_scale;
        method.m_curve = UIUtil::getCurve(curve);
        m_slots[slot].m_methods.push_back(method);
    }
}

void UICtrlManager::addAlphaMethod(int slot, float alpha, CURVE_TYPE curve) {
    if (m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_alpha.setup(m_slots[slot].m_object, alpha);
        UICtrl::Method method;
        method.m_method = &m_slots[slot].m_alpha;
        method.m_curve = UIUtil::getCurve(curve);
        m_slots[slot].m_methods.push_back(method);
    }
}

void UICtrlManager::addBrightMethod(int slot, float bright, CURVE_TYPE curve) {
    if (m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_bright.setup(m_slots[slot].m_object, bright);
        UICtrl::Method method;
        method.m_method = &m_slots[slot].m_bright;
        method.m_curve = UIUtil::getCurve(curve);
        m_slots[slot].m_methods.push_back(method);
    }
}

void UICtrlManager::addRotMethod(int slot, float rot, CURVE_TYPE curve) {
    if (m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_rot.setup(m_slots[slot].m_object, rot);
        UICtrl::Method method;
        method.m_method = &m_slots[slot].m_rot;
        method.m_curve = UIUtil::getCurve(curve);
        m_slots[slot].m_methods.push_back(method);
    }
}

void UICtrlManager::addMulColorMethod(int slot, const mm::Col3& color, CURVE_TYPE curve) {
    if (m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_mulColor.setup(m_slots[slot].m_object, color);
        UICtrl::Method method;
        method.m_method = &m_slots[slot].m_mulColor;
        method.m_curve = UIUtil::getCurve(curve);
        m_slots[slot].m_methods.push_back(method);
    }
}

void UICtrlManager::addAddColorMethod(int slot, const mm::Col3& color, CURVE_TYPE curve) {
    if (m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_addColor.setup(m_slots[slot].m_object, color);
        UICtrl::Method method;
        method.m_method = &m_slots[slot].m_addColor;
        method.m_curve = UIUtil::getCurve(curve);
        m_slots[slot].m_methods.push_back(method);
    }
}

void UICtrlManager::addMotionMethod(int slot, const char* file, const char* name) {
    UIMotionData* data;
    if (m_slots[slot].m_object != nullptr && (data = UIMotionLibrary::get()->find(file)) != nullptr) {
        m_slots[slot].m_motion.setup(m_slots[slot].m_object, data, name);
        UICtrl::Method method;
        method.m_method = &m_slots[slot].m_motion;
        method.m_curve = UIUtil::getCurve(CURVE_LINEAR);
        m_slots[slot].m_methods.push_back(method);
    }
}

void UICtrlManager::startCtrl(int slot, float duration, unsigned int flags, unsigned int param) {
    if (m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_ctrl.start(m_slots[slot].m_object, duration, m_slots[slot].m_methods, m_slots[slot].m_loop);
        m_slots[slot].m_methods.clear();
        m_slots[slot].m_flags = flags;
        m_slots[slot].m_object->m_flags |= 1;
        m_slots[slot].m_ctrlParam = param;
    }
}

void UICtrlManager::getDefaultTransfom(int slot, UITransform& transform) {
    if (slot >= 0 && slot <= 128u && m_slots[slot].m_object != nullptr) {
        transform = m_slots[slot].m_defTransform;
    }
}

void UICtrlManager::getDefaultDisplayInfo(int slot, UIDisplayInfo& info) {
    if (slot >= 0 && slot <= 128u && m_slots[slot].m_object != nullptr) {
        info = m_slots[slot].m_defDisplayInfo;
    }
}

void UICtrlManager::setSpeedFactor(int slot, float factor) {
    if (slot >= 0 && slot <= 128u && m_slots[slot].m_object != nullptr) {
        m_slots[slot].m_ctrl.m_speed = factor;
    }
}

void UICtrlManager::addCtrlObject(UICtrlObject* object) {
    if (object != nullptr) {
        object->addRef();
        m_ctrlObjects.push_back(object);
    }
}

void UICtrlManager::addUpdater(IUICtrlUpdater& updater) {
    if (!updater.m_node.intoNode()) {
        m_updaters.push_back(&updater.m_node);
    }
}

void UICtrlManager::delUpdater(IUICtrlUpdater& updater) {
    if (updater.m_node.intoNode()) {
        m_updaters.remove(&updater.m_node);
    }
}

bool UICtrlManager::isBusyCtrl(int slot) {
    if (slot < 0 || slot > 128u || m_slots[slot].m_object == nullptr) {
        return false;
    }
    if (m_slots[slot].m_ctrl.m_loop) {
        return true;
    }
    return !(m_slots[slot].m_ctrl.m_duration <= m_slots[slot].m_ctrl.m_time);
}

}  // namespace ui

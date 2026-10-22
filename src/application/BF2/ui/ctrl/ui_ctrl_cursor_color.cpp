#include "classes/ui/UICtrl.h"
#include "classes/ui/UICtrlCurve.h"
#include "classes/ui/UICtrlMethod.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlCursorColor.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/FixStr.h"
#include "ui/UIUtil.h"

namespace ui {

UICtrl::UICtrl()
    : m_object(nullptr), m_time(0.0f), m_unused(0.0f), m_duration(0.0f), m_loop(false), m_loopCount(0), m_methods(),
      m_speed(1.0f) {}

UICtrl::~UICtrl() {
    if (m_object != nullptr) {
        m_object->release();
        m_object = nullptr;
    }
}

void UICtrl::update(float step) {
    if (step == 0.0f || m_object == nullptr) {
        return;
    }
    UICtrlMethod::TimeInfo info;
    info.m_time = m_time;
    info.m_step = m_speed * step;
    info.m_duration = m_duration;
    if (m_duration == 0.0f && m_time == 0.0f) {
        // no time to run: every method at its end at once
        for (Method* it = m_methods.begin(); it != m_methods.end(); ++it) {
            if (it->m_method != nullptr) {
                it->m_method->execute(m_object, 1.0f, info);
            }
        }
        m_time = 1.0f;
    }
    if (!m_loop && m_duration <= m_time) {
        return;
    }
    m_time += info.m_step;
    bool finished = false;
    if (m_time >= m_duration) {
        if (!m_loop) {
            m_time = m_duration;
            finished = true;
        } else {
            m_time -= m_duration;
            m_loopCount++;
        }
    }
    for (Method* it = m_methods.begin(); it != m_methods.end(); ++it) {
        float rate;
        if (it->m_curve != nullptr) {
            rate = it->m_curve->calc(m_time, 0.0f, 1.0f, m_duration);
        } else {
            rate = m_time / m_duration;
        }
        if (it->m_method != nullptr) {
            it->m_method->execute(m_object, rate, info);
        }
    }
    if (finished) {
        stop();
    }
}

void UICtrl::stop() {
    if (m_object != nullptr) {
        m_object->release();
        m_object = nullptr;
    }
    m_time = 0.0f;
    m_duration = 0.0f;
    m_loop = false;
    m_loopCount = 0;
    m_methods.clear();
    m_speed = 1.0f;
    m_unused = 0.0f;
}

void UICtrl::start(UIObject* object, float duration, const mm::mtl::FixedVector<Method, 5>& methods, bool loop) {
    if (m_object != nullptr) {
        m_object->release();
        m_object = nullptr;
    }
    m_object = object;
    m_object->addRef();
    m_time = 0.0f;
    m_duration = duration;
    m_loop = loop;
    m_loopCount = 0;
    m_methods = methods;
    m_speed = 1.0f;
    m_unused = 0.0f;
}

UICtrlCursorColor::~UICtrlCursorColor() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

UICtrlCursorColor* UICtrlCursorColor::create(unsigned int handle, const CursorSetting& setting,
                                             UISelectObjList* list) {
    if (list == nullptr) {
        return nullptr;
    }
    list->addRef();
#line 47
    UICtrlCursorColor* ctrl = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UICtrlCursorColor(handle);
    if (ctrl == nullptr) {
        return nullptr;
    }
    ctrl->m_setting = setting;
    ctrl->m_list = list;
    ctrl->m_index = list->getIndex(false);
    ctrl->m_objHandle = handle;
    return ctrl;
}

void UICtrlCursorColor::open(int index) {
    if (m_list != nullptr) {
        m_index = index;
        m_list->setIndex(index);
    }
}

bool UICtrlCursorColor::inputChange(unsigned int index) {
    bool changed = false;
    UISelectObjList* list = m_list;
    if (index != 0xFFFFFFFF && list != nullptr && list->getSize() != 0) {
        setIndex(index);
        mm::mtl::FixStr<32> name;
        mm::mtl::FixStr<32> color;
        for (unsigned int i = 0; i < m_list->getSize(); i++) {
            UIObjectAcc acc(m_list->getObject(i));
            if (m_setting.m_dispName != nullptr) {
                bool disp = index == i;
                name.format(m_setting.m_dispName, i + 1);
                UIObjectAcc child(acc.searchChild(name.m_str));
                child.setDisp(disp);
            }
            if (m_setting.m_colorName != nullptr) {
                name.format(m_setting.m_colorName, i + 1);
                UIObjectAcc child(acc.searchChild(name.m_str));
                const char* colorName = index == i ? m_setting.m_selectColor : m_setting.m_normalColor;
                color.format("%s_mul", colorName);
                child.setMulColor(color.m_str);
                color.format("%s_add", colorName);
                child.setAddColor(color.m_str);
            }
        }
        changed = true;
    }
    return changed;
}

void UICtrlCursorColor::setDisp(bool disp) {
    inputChange(disp ? m_list->getIndex(false) : m_list->getSize() + 1);
}

void UICtrlCursorColor::update(const fw::UpdateInfo& info) {
    if (m_list != nullptr && m_list->getSize() != 0) {
        unsigned int index = m_list->getIndex(false);
        if (index != m_index) {
            m_index = index;
        }
    }
}

}  // namespace ui

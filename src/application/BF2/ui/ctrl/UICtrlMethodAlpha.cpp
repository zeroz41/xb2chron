#include "classes/ui/UICtrlMethodAlpha.h"
#include "classes/ui/UICtrlMethodBright.h"
#include "classes/ui/UICtrlMethodPos.h"
#include "classes/ui/UICtrlMethodScale.h"
#include "classes/ui/UICtrlMethodRot.h"
#include "classes/ui/UICtrlMethodMulColor.h"
#include "classes/ui/UICtrlMethodAddColor.h"
#include "classes/ui/UICtrlMethodMotion.h"
#include "classes/ui/UIMotionData.h"
#include "classes/ui/UIObject.h"
#include "ui/UIUtil.h"

namespace ui {

void UICtrlMethodAlpha::setup(const UIObject* object, float alpha) {
    m_from = object->m_displayInfo.getColorInfo()->m_mulColor.a;
    m_to = alpha;
}

void UICtrlMethodAlpha::execute(UIObject* object, float rate, const TimeInfo& info) {
    object->m_displayInfo.m_mulColor.a = m_from + (m_to - m_from) * rate;
}

void UICtrlMethodBright::setup(const UIObject* object, float bright) {
    m_from = object->m_displayInfo.m_addColor.r;
    m_to = bright;
}

void UICtrlMethodBright::execute(UIObject* object, float rate, const TimeInfo& info) {
    object->m_displayInfo.m_addColor.r = object->m_displayInfo.m_addColor.g = object->m_displayInfo.m_addColor.b =
        m_from + (m_to - m_from) * rate;
}

void UICtrlMethodPos::setup(const UIObject* object, const mm::Pnt<short>& pos) {
    mm::Pnt<short> offs;
    object->getDisplayOffset(0, offs);
    object->getPos(m_from);
    m_to = pos;
    m_from.x -= offs.x;
    m_from.y -= offs.y;
    m_to.x -= offs.x;
    m_to.y -= offs.y;
}

void UICtrlMethodScale::setup(const UIObject* object, const mm::Vec2& scale) {
    m_from = object->m_transform.m_scale;
    m_to = scale;
}

void UICtrlMethodScale::execute(UIObject* object, float rate, const TimeInfo& info) {
    float dx = m_to.x - m_from.x;
    float dy = m_to.y - m_from.y;
    object->m_transform.setScale(m_from.x + dx * rate, m_from.y + dy * rate);
}

void UICtrlMethodRot::setup(const UIObject* object, float rot) {
    m_from = object->m_transform.m_rotation;
    m_to = rot;
}

void UICtrlMethodRot::execute(UIObject* object, float rate, const TimeInfo& info) {
    object->m_transform.m_rotation = m_from + (m_to - m_from) * rate;
}

void UICtrlMethodMulColor::setup(const UIObject* object, const mm::Col3& color) {
    m_from = object->m_displayInfo.getColorInfo()->m_mulColor;
    m_to = color;
}

void UICtrlMethodMulColor::execute(UIObject* object, float rate, const TimeInfo& info) {
    mm::Col4 color(m_from.r + (m_to.r - m_from.r) * rate, m_from.g + (m_to.g - m_from.g) * rate,
                   m_from.b + (m_to.b - m_from.b) * rate, object->m_displayInfo.getColorInfo()->m_mulColor.a);
    object->m_displayInfo.m_mulColor = color;
}

void UICtrlMethodAddColor::setup(const UIObject* object, const mm::Col3& color) {
    m_from = object->m_displayInfo.getColorInfo()->m_addColor;
    m_to = color;
}

void UICtrlMethodAddColor::execute(UIObject* object, float rate, const TimeInfo& info) {
    mm::Col3 color;
    color.r = m_from.r + (m_to.r - m_from.r) * rate;
    color.g = m_from.g + (m_to.g - m_from.g) * rate;
    color.b = m_from.b + (m_to.b - m_from.b) * rate;
    object->setAddColor(color);
}

void UICtrlMethodMotion::setup(const UIObject* object, const UIMotionData* data, const char* name) {
    m_data = data;
    m_motion = data->searchMotion(name);
    m_frame = 0;
    mm::Pnt<short> pos;
    mm::Pnt<short> offs;
    object->getDisplayOffset(0, offs);
    object->getPos(pos);
    m_basePos.x = pos.x - offs.x;
    m_basePos.y = pos.y - offs.y;
    m_baseScale = object->m_transform.m_scale;
}

void UICtrlMethodMotion::execute(UIObject* object, float rate, const TimeInfo& info) {
    if (m_motion == -1) {
        return;
    }
    UIMotionData::MotionParam param = {};
    if (info.m_time == 0.0f) {
        m_data->getMotionParamDefault(m_motion, param);
        if (param.m_flags & 0x20) {
            object->m_displayInfo.m_mulColor.a = param.m_alpha;
        }
        float scaleX = 1.0f;
        if (param.m_flags & 0x4) {
            scaleX = param.m_scaleX;
        }
        float scaleY = 1.0f;
        if (param.m_flags & 0x8) {
            scaleY = param.m_scaleY;
        }
        object->m_transform.setScale(m_baseScale.x * scaleX, scaleY * m_baseScale.y);
    }
    float speed = m_data->getMotionLength(m_motion) / info.m_duration;
    m_data->getMotionParamDelta(m_motion, speed * info.m_time, speed * info.m_step, param);
    mm::Vec2 scale = object->m_transform.m_scale;
    object->m_transform.setScale(scale.x + m_baseScale.x * param.m_scaleX, scale.y + m_baseScale.y * param.m_scaleY);
    object->m_transform.m_rotation = object->m_transform.m_rotation + param.m_rot;
    mm::Pnt<short> pos;
    mm::Pnt<short> offs;
    object->getDisplayOffset(0, offs);
    m_basePos.x += param.m_posX;
    m_basePos.y += param.m_posY;
    pos.x = (short)m_basePos.x + offs.x;
    pos.y = (short)m_basePos.y + offs.y;
    object->setPos(pos);
    float alpha = object->m_displayInfo.getColorInfo()->m_mulColor.a + param.m_alpha;
    if (alpha > 1.0f) {
        alpha = 1.0f;
    }
    if (alpha < 0.0f) {
        alpha = 0.0f;
    }
    object->m_displayInfo.m_mulColor.a = alpha;
}

}  // namespace ui

#ifndef CLASSES_UI_UICTRLREVOLVESELECT_H
#define CLASSES_UI_UICTRLREVOLVESELECT_H

#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlSimple.h"
#include "classes/ui/UISelectObjList.h"
#include "mm/Pnt.h"
#include "ui/UIUtil.h"

namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B745E8; lays a list's objects out on a circle (or an arc) around a center and turns it so the
// selected one comes to the front, over a time (the field names are not the original's)
class UICtrlRevolveSelect : public ::ui::UICtrlObject {
public:
    // create's
    struct RevolveSetting {
        RevolveSetting()
            : m_angleRange(0), m_type(0), m_direction(0), m_rollTime(0.0f), m_radius(0), m_startAngle(0),
              m_scaleRate(0.5f), m_radiusY(0), m_priorityBase(0), m_rollCurve(CURVE_LINEAR),
              m_moveCurve(CURVE_LINEAR), m_colorRate(0.5f) {}
        unsigned short m_angleRange;  // degrees the objects spread over (360: all around, else an arc of it)
        unsigned char m_type;  // 0: a circle with a pointer (m_pointer), 1 and 2: a depth-sorted ring on its side
        unsigned char m_direction;  // 0: each object a step further on the negative angle, else the positive
        float m_rollTime;      // the time a turn to a new selection takes (0: it jumps)
        mm::Pnt<short> m_center;
        unsigned int m_radius;
        float m_moveTime;  // the time moveCenterOffset's move takes
        unsigned short m_startAngle;  // type 0's angle of the first object (types 1 and 2 start at 90)
        float m_scaleRate;  // types 1 and 2: how much smaller the objects at the back are
        int m_radiusY;      // types 1 and 2: the ring's other radius
        unsigned int m_priorityBase;  // types 1 and 2: added to the display priority
        CURVE_TYPE m_rollCurve;
        CURVE_TYPE m_moveCurve;
        float m_colorRate;  // how much darker the objects away from the front are
    };
    // inline: 3.0.1 has no out-of-line copy (1.0.0's is at 0x71006D0248, create holds its stores)
    UICtrlRevolveSelect(unsigned int handle)
        : UICtrlObject(handle), m_setting(), m_startAngle(0), m_list(nullptr), m_index(0), m_targetAngle(0.0f),
          m_angle(0.0f), m_roll(), m_centerOffset(0, 0), m_move(), m_pointer(0) {}
    virtual ~UICtrlRevolveSelect();  // slot 0
    virtual void update(const fw::UpdateInfo& info);  // slot 2
    // a ring on the objects of list (it holds a reference to it); null without one
    static UICtrlRevolveSelect* create(unsigned int handle, const RevolveSetting& setting, UISelectObjList* list);
    void reset();  // turns to the list's selection at once
    void setIndex(int index, bool anim);  // turns to index, over m_rollTime when anim
    // inline: 3.0.1 has no out-of-line copy (1.0.0's is at 0x71006D07A0)
    void resetAngelRange(unsigned short range) { m_setting.m_angleRange = range; }
    // inline: 3.0.1 has no out-of-line copy (1.0.0's is at 0x71006D07A8, update holds its code)
    void getCenterPos(mm::Pnt<short>& pos) const {
        pos.x = m_setting.m_center.x + m_centerOffset.x;
        pos.y = m_setting.m_center.y + m_centerOffset.y;
    }
    void moveCenterOffset(const mm::Pnt<short>& offset, bool anim);  // over m_moveTime when anim
    // inline: 3.0.1 has no out-of-line copy (1.0.0's is at 0x71006D08C0)
    bool isRolling() const { return m_roll.isBusy(); }
    bool isMoving() const;
    void updateObject(float angle, const mm::Pnt<short>& offset);
    // the angle between two objects (inline: 3.0.1 has no out-of-line copy, 1.0.0's is at 0x71006D0E28 and
    // reset, setIndex and updateObject hold its code)
    float getAngleStep() {
        float step;
        if (static_cast<unsigned int>(m_list->getSize()) <= 1) {
            step = m_setting.m_angleRange;
        } else if (m_setting.m_angleRange == 360) {
            step = m_setting.m_angleRange / static_cast<float>(static_cast<unsigned int>(m_list->getSize()));
        } else {
            step = m_setting.m_angleRange / static_cast<float>(static_cast<unsigned int>(m_list->getSize() - 1));
        }
        return m_setting.m_direction == 0 ? -step : step;
    }

    RevolveSetting m_setting;
    int m_startAngle;  // the first object's angle: 90 for types 1 and 2, else m_setting.m_startAngle
    UISelectObjList* m_list;  // a reference held until the destructor
    int m_index;              // the selection it turned to
    float m_targetAngle;      // the angle a turn ends at
    float m_angle;            // the ring's angle
    UICtrlSimple<1> m_roll;   // the angle on a turn
    mm::Pnt<short> m_centerOffset;  // added to m_setting.m_center
    UICtrlSimple<2> m_move;         // the center offset on moveCenterOffset's move
    unsigned int m_pointer;  // type 0: an object put on the center and turned with the ring (none: 0)
};
}  // namespace ui

#endif

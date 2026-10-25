#ifndef CLASSES_UI_UITRANSFORM_H
#define CLASSES_UI_UITRANSFORM_H

#include "mm/Pnt.h"

namespace ui {
// table 0x7100B75818; an object's position and scale (UIObjectBase keeps one at +0x20)
class UITransform {
public:
    UITransform();
    virtual ~UITransform();  // slot 0
    // out of line (UICtrlManager's copies call it; the return type is not known)
    void operator=(const UITransform& other);
    void setPos(short x, short y);
    void setScale(float x, float y);
    void syncParent();  // nothing (1.0.0's setParent did nothing either)
    mm::Pnt<short> m_pos;        // setPos's
    unsigned char pad_0C[0x4];
    float m_scaleX;              // setScale's
    float m_scaleY;
    unsigned char pad_18[0x8];
    float m_rotation;  // UIObjectAcc::getRot/setRot
    bool m_changed;              // setPos and setScale set it when they change something
};
}  // namespace ui

#endif

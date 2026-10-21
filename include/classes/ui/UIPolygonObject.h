#ifndef CLASSES_UI_UIPOLYGONOBJECT_H
#define CLASSES_UI_UIPOLYGONOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObject.h"

namespace ui {
// table 0x7100B74E98
class UIPolygonObject : public ::ui::UIObject {
public:
    virtual ~UIPolygonObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual void apply();  // slot 6
    virtual void duplicateImpl(unsigned int);  // slot 9
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif

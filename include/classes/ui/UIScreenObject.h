#ifndef CLASSES_UI_UISCREENOBJECT_H
#define CLASSES_UI_UISCREENOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObject.h"

namespace ui {
// table 0x7100B74EF8
class UIScreenObject : public ::ui::UIObject {
public:
    virtual ~UIScreenObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual void duplicateImpl(unsigned int);  // slot 9
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif

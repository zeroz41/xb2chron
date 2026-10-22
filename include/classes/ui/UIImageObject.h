#ifndef CLASSES_UI_UIIMAGEOBJECT_H
#define CLASSES_UI_UIIMAGEOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObject.h"

namespace ui {
// table 0x7100B74DD0
class UIImageObject : public ::ui::UIObject {
public:
    virtual ~UIImageObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual unsigned int duplicateImpl(unsigned int);  // slot 9
    virtual void changeBin(void const*);  // slot 10
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif

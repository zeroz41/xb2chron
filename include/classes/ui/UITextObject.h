#ifndef CLASSES_UI_UITEXTOBJECT_H
#define CLASSES_UI_UITEXTOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObject.h"

namespace mm { class Vec2; }
namespace mm { template <typename> class Pnt; }

namespace ui {
// table 0x7100B74F58
class UITextObject : public ::ui::UIObject {
public:
    virtual ~UITextObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual void apply();  // slot 6
    virtual void getDisplayOffset(unsigned short, mm::Pnt<short>&) const;  // slot 7
    virtual void getTransformPosOffs(mm::Vec2&);  // slot 8
    virtual void duplicateImpl(unsigned int);  // slot 9
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif

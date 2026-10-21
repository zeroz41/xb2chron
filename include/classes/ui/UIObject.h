#ifndef CLASSES_UI_UIOBJECT_H
#define CLASSES_UI_UIOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectBase.h"

namespace mm { class Vec2; }
namespace mm { template <typename> class Pnt; }

namespace ui {
// table 0x7100B756B8
class UIObject : public ::ui::UIObjectBase {
public:
    virtual ~UIObject();  // slot 0
    virtual void update();  // slot 2
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual void apply();  // slot 6
    virtual void getDisplayOffset(unsigned short, mm::Pnt<short>&) const;  // slot 7
    virtual void getTransformPosOffs(mm::Vec2&);  // slot 8
    virtual void duplicateImpl(unsigned int) = 0;  // slot 9
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif

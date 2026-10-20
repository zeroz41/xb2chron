#ifndef CLASSES_UI_UILAYOUTOBJECT_H
#define CLASSES_UI_UILAYOUTOBJECT_H

#include "classes/ui/UIObject.h"

namespace mm { template <typename> class Pnt; }

namespace ui {
// table 0x7100B74E38
class UILayoutObject : public ::ui::UIObject {
public:
    virtual ~UILayoutObject();  // slot 0
    virtual void update();  // slot 2
    virtual void setInitialize();  // slot 3
    virtual void getRTTI() const;  // slot 5
    virtual void apply();  // slot 6
    virtual void getDisplayOffset(unsigned short, mm::Pnt<short>&) const;  // slot 7
    virtual void duplicateImpl(unsigned int);  // slot 9
};
}  // namespace ui

#endif

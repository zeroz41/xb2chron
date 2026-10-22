#ifndef CLASSES_WND_WINDOBJECT_H
#define CLASSES_WND_WINDOBJECT_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "wnd/Transform.h"

namespace wnd { class Shape; }

namespace wnd {
// table 0x7100B818C0; counted (its constructor clears the count at 8)
class WindObject : public mm::mtl::ReferenceObject {
public:
    virtual ~WindObject();  // slot 0

    unsigned char pad_10[0x20];
    Transform m_transform;  // the constructor copies its create-info's info.pTransform
    Shape* m_shape;  // the constructor's info.pShape, referenced; the destructor releases it
    unsigned char pad_58[0x30];  // fields: size from what the constructor writes
};
}  // namespace wnd

#endif

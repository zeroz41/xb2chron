#ifndef CLASSES_FW_VISIBLEOBJECT_H
#define CLASSES_FW_VISIBLEOBJECT_H

namespace fw {
// table 0x7100B42298
class VisibleObject {
public:
    virtual ~VisibleObject();  // slot 0
    virtual void update();  // slot 2
};
}  // namespace fw

#endif

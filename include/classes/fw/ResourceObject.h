#ifndef CLASSES_FW_RESOURCEOBJECT_H
#define CLASSES_FW_RESOURCEOBJECT_H

namespace fw {
// table 0x7100B42B18
class ResourceObject {
public:
    virtual ~ResourceObject();  // slot 0
    virtual void vf2() = 0;  // slot 2
    virtual void vf3() = 0;  // slot 3
};
}  // namespace fw

#endif

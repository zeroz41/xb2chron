#ifndef CLASSES_FW_RESOURCEOBJECT_H
#define CLASSES_FW_RESOURCEOBJECT_H

namespace fw {
// table 0x7100B42B18
class ResourceObject {
public:
    virtual ~ResourceObject();  // slot 0
    virtual void update() = 0;  // slot 2
    virtual void valid() const = 0;  // slot 3
};
}  // namespace fw

#endif

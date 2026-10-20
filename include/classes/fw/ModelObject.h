#ifndef CLASSES_FW_MODELOBJECT_H
#define CLASSES_FW_MODELOBJECT_H

namespace fw {
// table 0x7100B42270
class ModelObject {
public:
    virtual ~ModelObject();  // slot 0
    virtual void update();  // slot 2
};
}  // namespace fw

#endif

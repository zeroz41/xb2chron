#ifndef CLASSES_FW_UPDATABLEOBJECT_H
#define CLASSES_FW_UPDATABLEOBJECT_H

namespace fw { class ObjectEvent; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B425F0
class UpdatableObject {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~UpdatableObject();  // slot 1
    virtual void initialize();  // slot 3
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 4
    virtual void onEvent(fw::ObjectEvent const&);  // slot 5
    unsigned char pad_8[0xD8];  // fields: size from its derived classes
};
}  // namespace fw

#endif

#ifndef CLASSES_FW_UPDATABLEOBJECT_H
#define CLASSES_FW_UPDATABLEOBJECT_H

#include "mm/mtl/RTTI.h"
namespace fw { class ObjectEvent; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B425F0
class UpdatableObject {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~UpdatableObject();  // slot 1
    virtual void initialize();  // slot 3
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 4
    virtual void onEvent(fw::ObjectEvent const&);  // slot 5
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_8[0xD8];  // fields: size from its derived classes
};
}  // namespace fw

#endif

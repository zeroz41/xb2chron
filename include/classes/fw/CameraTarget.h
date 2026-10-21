#ifndef CLASSES_FW_CAMERATARGET_H
#define CLASSES_FW_CAMERATARGET_H

#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B45DB0
class CameraTarget {
public:
    virtual ~CameraTarget();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 3
    virtual void requestResetCamera();  // slot 4
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_8[0x8];  // fields: size from its derived classes
};
}  // namespace fw

#endif

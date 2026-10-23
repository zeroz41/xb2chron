#ifndef CLASSES_FW_CAMERATARGET_H
#define CLASSES_FW_CAMERATARGET_H

#include "mm/mtl/RTTI.h"
#include "classes/mm/mtl/ReferenceObject.h"
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B45DB0; counted by mm::mtl::IntrusivePtr (GfGamePlayerCamera holds its PlayerCameraTarget in one and
// releases it as reference_object.h does: the count at 8, the deleting destructor in slot 1)
class CameraTarget : public ::mm::mtl::ReferenceObject {
public:
    // inline: the table and this unit's copies of its slots are PlayerCameraTarget's unit's
    virtual ~CameraTarget() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 3
    virtual void requestResetCamera() {}  // slot 4
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif

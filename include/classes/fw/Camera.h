#ifndef CLASSES_FW_CAMERA_H
#define CLASSES_FW_CAMERA_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "classes/mm/mtl/ReferenceObject.h"
namespace fw { class UpdateInfo; }

namespace fw {
// the camera manager's ordering of a camera (SubViewCamera's is 55)
enum CAMERA_PRIO {};

// table none (its derived classes'); counted by mm::mtl::IntrusivePtr (SubViewCamera::create returns one).
// Its destructor is inline: only the deleting one is out of line (0x7100162460, with the table), and a derived
// class's complete destructor returns without calling a base one.
class Camera : public ::mm::mtl::ReferenceObject {
public:
    Camera(CAMERA_PRIO prio);
    virtual ~Camera() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const;  // slot 3
    virtual void onPush() {}  // slot 4
    virtual void onPop() {}  // slot 5
    virtual void onActivate() {}  // slot 6
    virtual void onDeactivate() {}  // slot 7
    virtual void update(fw::UpdateInfo const&) {}  // slot 8
    virtual void updateViewMatrix();  // slot 9
    void setLookAt(const mm::Vec3& eye, const mm::Vec3& target, float roll);
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_c[0x9C];
};
}  // namespace fw

#endif

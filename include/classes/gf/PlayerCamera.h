#ifndef CLASSES_GF_PLAYERCAMERA_H
#define CLASSES_GF_PLAYERCAMERA_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B45AE8
class PlayerCamera : public ::fw::Camera {
public:
    virtual ~PlayerCamera();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const;  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
    virtual void updateViewMatrix();  // slot 9
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif

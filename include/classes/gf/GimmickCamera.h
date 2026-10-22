#ifndef CLASSES_GF_GIMMICKCAMERA_H
#define CLASSES_GF_GIMMICKCAMERA_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B45E68
class GimmickCamera : public ::fw::Camera {
public:
    virtual ~GimmickCamera();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const;  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif

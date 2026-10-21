#ifndef CLASSES_GF_GFMENUBLADECREATECAMERA_H
#define CLASSES_GF_GFMENUBLADECREATECAMERA_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5FFE8
class GfMenuBladeCreateCamera : public ::fw::Camera {
public:
    virtual ~GfMenuBladeCreateCamera();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void getName() const;  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 8
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GIMMICKCAMERA_H
#define CLASSES_GF_GIMMICKCAMERA_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/Camera.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"

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

    // the camera file's entry of that name, placed at pos turned by rotY
    static mm::mtl::IntrusivePtr<GimmickCamera> create(const char* name, const mm::Vec3& pos, float rotY);
    void play();
    bool isPlayEnd() const;
    bool isLoaded() const;
    void setAuto(bool on);
};
}  // namespace gf

#endif

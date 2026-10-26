#ifndef CLASSES_GF_MAPJUMPCAMERA_H
#define CLASSES_GF_MAPJUMPCAMERA_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/Camera.h"

namespace gf {
// table 0x7100B6A848 (gf_req_command's: every slot inline, so the table is emitted where execMapjump creates one).
// The class name is getName's; the namespace is inferred.
// the camera GfReqCommand::execMapjump pushes while it moves the party (its name is getName's)
class MapjumpCamera : public ::fw::Camera {
public:
    MapjumpCamera() : ::fw::Camera(::fw::CAMERA_PRIO(9)) {}
    virtual ~MapjumpCamera() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const { return "MapjumpCamera"; }  // slot 3
    static mm::mtl::RTTI m_rtti;
};

}  // namespace gf

#endif

#ifndef CLASSES_EVENT_CAMINTERFACE_H
#define CLASSES_EVENT_CAMINTERFACE_H

#include "classes/fw/Camera.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { enum CAMERA_TYPE : int; }

namespace event {
// table 0x7100B3C778
class CamInterface : public ::fw::Camera {
public:
    // inline (1.0.0 had it out of line at 0x71000AD290: CamManager::init builds the interfaces, and with them the table)
    CamInterface(fw::CAMERA_TYPE type) : fw::Camera(static_cast<fw::CAMERA_PRIO>(0xf)), m_type(type), pad_ac(0), pad_b0(0), m_self(this) {
        setLookAt(mm::Vec3(4.0f, 5.0f, 5.0f), mm::Vec3(0.0f, 1.0f, 0.0f), 0.0f);
    }
    virtual ~CamInterface() {}  // slot 0 (inline: in the unit's tail at 0x710014C3AC; releases m_self)
    fw::CAMERA_TYPE m_type;  // 0xa8: the constructor's (the name is not the original's)
    bool pad_ac;
    unsigned int pad_b0;
    // the interface holds a reference to itself (the destructor releases it); the name is not the original's
    mm::mtl::IntrusivePtr<CamInterface> m_self;  // 0xb8
};
}  // namespace event

#endif

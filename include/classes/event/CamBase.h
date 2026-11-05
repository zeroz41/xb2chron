#ifndef CLASSES_EVENT_CAMBASE_H
#define CLASSES_EVENT_CAMBASE_H

#include "mm/Vec3.h"

namespace event { class FrameInfo; }
namespace mm { class Col4; }

namespace event {
// table none (its derived classes')
class CamBase {
public:
    // inline: the constructors of CamFree (CamManager's), CamField, CamHands and CamMotion (CamObj's) store these
    // values for every camera before its own table, so they are the base's
    CamBase() : pad_8(0) {
        pad_10.x = 0.0f;
        pad_10.y = 1.0f;
        pad_10.z = 2.0f;
        pad_20.x = 0.0f;
        pad_20.y = 1.0f;
        pad_20.z = 1.0f;
        pad_30 = 40.0f;
        pad_34 = 0.0f;
        m_near = 0.5f;
        m_far = 40000.0f;
    }
    virtual ~CamBase() {}  // slot 0
    virtual void update(event::FrameInfo const&) = 0;  // slot 2
    virtual void render(mm::Col4 const&) {}  // slot 3
    virtual void tail() {}  // slot 4
    unsigned char pad_8;  // 0x8: CamFree's constructor clears it
    unsigned char pad_9[0x7];
    // 0x10 and 0x20: two vectors, (0, 1, 2) and (0, 1, 1) from CamFree's constructor. mm::Vec3, so the class is
    // 16-aligned: the original's CamManager singleton is 0x100 bytes (its last member CamFree rounds up to 0x70), and
    // CamHands::setTar passes this+0x10 to DataManager::axis2tar as a const mm::Vec3&
    mm::Vec3 pad_10;
    mm::Vec3 pad_20;
    float pad_30;  // 0x30: 40 from CamFree's constructor
    float pad_34;  // 0x34: 0 from CamFree's constructor
    // the near and far clip distances ScriptCamNearfar sets from EVT_nearfar; the name is not the original's
    float m_near;  // 0x38
    float m_far;   // 0x3c
};
}  // namespace event

#endif

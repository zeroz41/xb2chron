#ifndef CLASSES_EVENT_CAMFREE_H
#define CLASSES_EVENT_CAMFREE_H

#include "classes/event/CamBase.h"
#include "classes/ml/IWorkEvent.h"

namespace event { class FrameInfo; }
namespace ml { class EventView; }

namespace event {
// table 0x7100B3C818
class CamFree : public ::event::CamBase, public ::ml::IWorkEvent {
public:
    // inline: CamManager's constructor (1.0.0 0x71000B5DE8, inlined in Singleton<CamManager>::getPtr) builds it
    CamFree() : m_flags(0), pad_49(0), pad_4a(0), pad_4c(0), pad_50(0.0f), pad_54(5.0f), pad_60(0) {
        pad_8 = 0;
        pad_10[0] = 0.0f;
        pad_10[1] = 1.0f;
        pad_10[2] = 2.0f;
        pad_20[0] = 0.0f;
        pad_20[1] = 1.0f;
        pad_20[2] = 1.0f;
        pad_30 = 40.0f;
        pad_34 = 0.0f;
        m_near = 0.5f;
        m_far = 40000.0f;
    }
    virtual ~CamFree();  // slot 0
    virtual void update(event::FrameInfo const&);  // slot 2
    virtual void OnMouseButtonDown(ml::EventView*);  // slot 5
    virtual void OnMouseMove(ml::EventView*);  // slot 6
    virtual void OnMouseButtonUp(ml::EventView*);  // slot 7
    virtual void OnKeyUp(ml::EventView*);  // slot 8
    virtual void OnKeyDown(ml::EventView*);  // slot 9
    // bit 0 is set while the camera is attached to the scene's view: the destructor then detaches it (ml::WinView's
    // detachWorkEvent); the name is not the original's
    unsigned char m_flags;  // 0x48
    unsigned char pad_49;
    unsigned short pad_4a;
    unsigned int pad_4c;
    float pad_50;  // 0x50: 0 from the constructor
    float pad_54;  // 0x54: 5 from the constructor
    unsigned char pad_58[0x8];
    unsigned int pad_60;  // 0x60
};
}  // namespace event

#endif

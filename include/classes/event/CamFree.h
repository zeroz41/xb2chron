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
};
}  // namespace event

#endif

#ifndef CLASSES_EVENT_BOUMANAGER_H
#define CLASSES_EVENT_BOUMANAGER_H

#include "classes/ml/IWorkEvent.h"

namespace event { enum MSG_TYPE : int; }
namespace ml { class EventView; }

#include "mm/mtl/FixedVector.h"
namespace event { class IBouCallback; }

namespace event {
// a base of event::BouManager no evidence names yet
class TUnk_B3DA40 {
public:
    virtual ~TUnk_B3DA40();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
    virtual void OnMouseButtonDown(ml::EventView*) = 0;
    virtual void OnMouseMove(ml::EventView*) = 0;
    virtual void OnMouseButtonUp(ml::EventView*) = 0;
    virtual void OnKeyDown(ml::EventView*) = 0;
    virtual void OnKeyUp(ml::EventView*) = 0;
};
// a base of event::BouManager no evidence names yet
class TUnk_B3DA90 {
public:
    virtual ~TUnk_B3DA90();
};
// table 0x7100B3DA40; base at 0x0 unknown (TUnk_B3DA40), base at 0x8 unknown (TUnk_B3DA90)
class BouManager : public TUnk_B3DA40, public TUnk_B3DA90, public ::ml::IWorkEvent {
public:
    virtual ~BouManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    virtual void OnMouseButtonDown(ml::EventView*);  // slot 3
    virtual void OnMouseMove(ml::EventView*);  // slot 4
    virtual void OnMouseButtonUp(ml::EventView*);  // slot 5
    virtual void OnKeyDown(ml::EventView*);  // slot 6
    virtual void OnKeyUp(ml::EventView*);  // slot 7
    // 1.0.0's BouManager::render; out of line
    void render();
    // 1.0.0's BouManager::clear (0x7100105D5C) and endActive (0x7100105DD8); 3.0.1 inlines them into OnEventProc
    void clear();
    void endActive() { m_flags &= ~4; }
    // bit 1: attached to the view (create sets it, clear detaches), bit 2: active (endActive clears it) (the name is not the original's)
    unsigned int m_flags;  // 0x18
    unsigned int m_debugFlags;  // 0x1c setDebugEnable's (the name is not the original's)
    unsigned char pad_20[0x18];
    mm::mtl::FixedVector<IBouCallback*, 1024> m_callbacks;  // 0x38 push/pop (the name is not the original's)
    mm::mtl::FixedVector<IBouCallback*, 1024> m_actives;  // 0x2040 updateActive fills it (the name is not the original's; element type inferred)
};
}  // namespace event

#endif

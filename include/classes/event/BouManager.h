#ifndef CLASSES_EVENT_BOUMANAGER_H
#define CLASSES_EVENT_BOUMANAGER_H

#include "classes/ml/IWorkEvent.h"

namespace event { enum MSG_TYPE : int; }
#include "classes/ml/EventView.h"

#include "mm/mtl/FixedVector.h"
#include "mm/Pnt.h"
#include "mm/mtl/Bitflag.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
namespace event { class IBouCallback; }

namespace event {
// table 0x7100B3DA40; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::BouManager>
class BouManager : public IManager, public mm::mtl::Singleton<BouManager>, public ::ml::IWorkEvent {
public:
    virtual ~BouManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    virtual bool OnMouseButtonDown(ml::EventView*);  // slot 3
    virtual bool OnMouseMove(ml::EventView*);  // slot 4
    virtual bool OnMouseButtonUp(ml::EventView*);  // slot 5
    virtual bool OnKeyDown(ml::EventView*);  // slot 6
    virtual bool OnKeyUp(ml::EventView*);  // slot 7
    // 1.0.0's BouManager::render; out of line
    void render();
    // 1.0.0's BouManager::clear (0x7100105D5C) and endActive (0x7100105DD8); 3.0.1 inlines them into OnEventProc
    void clear();
    void endActive() { m_flags.set(2, false); }
    void updateActive(const mm::Pnt<int>& pos);
    // bit 1: attached to the view (create sets it, clear detaches), bit 2: active (endActive clears it) (the name is not the original's)
    // bit 3: a key is held (OnKeyDown/OnKeyUp), which keeps a drag from starting. Bitflag words, not plain ints:
    // the slots load each word on its own, as ManiManager's do
    mm::mtl::Bitflag<32> m_flags;  // 0x18
    mm::mtl::Bitflag<32> m_debugFlags;  // 0x1c setDebugEnable's (the name is not the original's)
    unsigned char pad_20[0x8];
    // where the drag began (OnMouseButtonDown) and the pointer's offset from it (OnMouseMove) (the names are not
    // the original's)
    mm::Pnt<int> m_downPos;  // 0x28
    mm::Pnt<int> m_dragOfs;  // 0x30
    mm::mtl::FixedVector<IBouCallback*, 1024> m_callbacks;  // 0x38 push/pop (the name is not the original's)
    mm::mtl::FixedVector<IBouCallback*, 1024> m_actives;  // 0x2040 updateActive fills it (the name is not the original's; element type inferred)
};
}  // namespace event

#endif

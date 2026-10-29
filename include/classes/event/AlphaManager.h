#ifndef CLASSES_EVENT_ALPHAMANAGER_H
#define CLASSES_EVENT_ALPHAMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; class AlphaObj; }

namespace event {
// table 0x7100B3C120; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::AlphaManager>
class AlphaManager : public IManager, public mm::mtl::Singleton<AlphaManager> {
public:
    virtual ~AlphaManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2

private:
    unsigned int m_flags;  // 0x10 bit 0: update walks the objects (the name is not the original's)
    unsigned char pad_14[0x4];
    // update and render walk it; render deletes (slot 1) and erases each finished one; the name is not the original's
    mm::mtl::FixedVector<AlphaObj*, 256> m_objs;  // 0x18 (count at 0x818)
};
}  // namespace event

#endif

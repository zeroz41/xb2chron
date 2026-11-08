#ifndef CLASSES_EVENT_EVTXTMANAGER_H
#define CLASSES_EVENT_EVTXTMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/Bitflag.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D9D8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::EvtxtManager>
class EvtxtManager : public IManager, public mm::mtl::Singleton<EvtxtManager> {
public:
    virtual ~EvtxtManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void render();
    // the folder render prints (_ZN5event12EvtxtManager10EVTXT_PATHE, "C:/MonolithSoft/BF2/evtxt")
    static const char* EVTXT_PATH;
    // bit 0: a position write is reserved (1.0.0's reserve(bool)/isReserve() set and test it; render draws
    // "POS RESERVING.." then); 1.0.0's constructor zeroes it. The name is not the original's
    mm::mtl::Bitflag<32> m_flags;  // 0x10
};
}  // namespace event

#endif

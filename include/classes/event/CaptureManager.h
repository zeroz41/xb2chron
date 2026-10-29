#ifndef CLASSES_EVENT_CAPTUREMANAGER_H
#define CLASSES_EVENT_CAPTUREMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixStr.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D988; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::CaptureManager>
class CaptureManager : public IManager, public mm::mtl::Singleton<CaptureManager> {
public:
    virtual ~CaptureManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void ready();
    void start();
    void stop();
    void update();
    void render();

    // OnEventProc: bit 0 gates ready(), bits 0..1 == 1 gate start(), bit 1 gates stop(); the name is not the original's
    unsigned int m_flags;  // @0x10
    unsigned char pad_14[0xc];
    // names render appends (FixStr<16>: `m_nLen < LEN` asserted at +0x10 of each 0x14-byte element); the name is not
    // the original's
    mm::mtl::FixedVector<mm::mtl::FixStr<16>, 512> m_names;  // 0x20 (count at 0x2820)
};
}  // namespace event

#endif

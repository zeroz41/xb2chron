#ifndef CLASSES_EVENT_CAPTUREMANAGER_H
#define CLASSES_EVENT_CAPTUREMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

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
};
}  // namespace event

#endif

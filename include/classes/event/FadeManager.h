#ifndef CLASSES_EVENT_FADEMANAGER_H
#define CLASSES_EVENT_FADEMANAGER_H

#include "classes/event/FadeCtrl.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }
namespace mm { class Col4; }

namespace event {
// table 0x7100B3CF60; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::FadeManager>
class FadeManager : public IManager, public mm::mtl::Singleton<FadeManager> {
public:
    // out of line: Singleton<FadeManager>::getPtr registers it with __cxa_atexit (see DofManager.h)
    virtual ~FadeManager();  // slot 0
    FadeManager();  // out of line (Singleton<FadeManager>::getPtr calls it)
    // color null: the fade keeps its color
    void play(bool in, unsigned int frame, FadeCtrl::PRIO prio, const mm::Col4* color);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif

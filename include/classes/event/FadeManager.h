#ifndef CLASSES_EVENT_FADEMANAGER_H
#define CLASSES_EVENT_FADEMANAGER_H

#include "classes/event/FadeCtrl.h"
#include "classes/event/FadePlanner.h"
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
    FadeManager();  // out of line at 0x71000F54E4; Singleton<FadeManager>::getPtr inlines it in its own unit
    // the symbol _ZNK5event11FadeManager8isFadingEv (SeqManager::end_fadewait::update waits while it is true)
    bool isFading() const;
    // color null: the fade keeps its color
    void play(bool in, unsigned int frame, FadeCtrl::PRIO prio, const mm::Col4* color);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2

    unsigned int pad_10;  // 0x10 (the constructor zeroes it)
    unsigned int pad_14;  // 0x14 (the constructor zeroes it)
    FadePlanner pad_18;  // 0x18 (update calls its update)
};
}  // namespace event

#endif

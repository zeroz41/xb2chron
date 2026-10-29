#ifndef CLASSES_EVENT_DOFMANAGER_H
#define CLASSES_EVENT_DOFMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3CDC0; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::DofManager>
class DofManager : public IManager, public mm::mtl::Singleton<DofManager> {
public:
    // out of line: Singleton<DofManager>::getPtr hands __cxa_atexit its D1 (an alias of a strong D2), which an inline empty
    // destructor would let the optimizer drop (evt_post's entries keep the call)
    virtual ~DofManager();  // slot 0
    DofManager();  // out of line (Singleton<DofManager>::getPtr calls it)
    // evt_post.playDof's entries (the plain and the detailed form)
    void play(int type, int frame);
    void play(int type, float p0, float p1, float p2, float p3, float p4, float p5, int frame, bool flag,
              const char* name);
    void playSimple(int type, int frame);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // 1.0.0's clear() (0x71000D88D4) only calls stop()
    void clear();
    void stop();
    void update();
    void render();
};
}  // namespace event

#endif

#ifndef CLASSES_EVENT_RANDMANAGER_H
#define CLASSES_EVENT_RANDMANAGER_H

namespace event { enum MSG_TYPE : int; }

#include "classes/event/CmdQueue.h"

namespace event {
// a base of event::RandManager no evidence names yet
class TUnk_B3D3C0 {
public:
    virtual ~TUnk_B3D3C0();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::RandManager no evidence names yet
class TUnk_B3D3E8 {
public:
    virtual ~TUnk_B3D3E8();
};
// table 0x7100B3D3C0; base at 0x0 unknown (TUnk_B3D3C0), base at 0x8 unknown (TUnk_B3D3E8)
class RandManager : public TUnk_B3D3C0, public TUnk_B3D3E8 {
public:
    virtual ~RandManager();  // slot 0
    RandManager();  // out of line (Singleton<RandManager>::getPtr calls it)
    // evt_rand.play: returns false while the script has to wait
    bool play(int no);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // 1.0.0's RandManager::clear (0x71000E996C) and update (0x71000E99BC); 3.0.1 inlines them into OnEventProc
    void clear() {
        m_queue.clear();
        pad_990 = 0;
        m_flags = 0;
    }
    void update() {
        if ((m_flags & 1) && (pad_990 & 1)) {
            m_queue.update();
            if (m_queue.empty()) {
                pad_990 &= ~1;
            }
        }
    }
    unsigned int m_flags;  // 0x10 (the name is not the original's)
    unsigned char pad_14[0x2c];
    CmdQueue<8, 0> m_queue;  // 0x40 (the name is not the original's)
    unsigned int pad_990;  // bit 0: playing (update clears it when the queue is empty)
};
}  // namespace event

#endif

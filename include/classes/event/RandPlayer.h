#ifndef CLASSES_EVENT_RANDPLAYER_H
#define CLASSES_EVENT_RANDPLAYER_H

#include "classes/event/CmdQueue.h"

namespace event {
// table 0x7100B3D3A0
class RandPlayer {
public:
    class Reset;
    class Wait;
    class Warp;
    virtual ~RandPlayer();  // slot 0
    // 1.0.0's RandPlayer::clear/update/isPlaying (out of line there; 3.0.1 inlines them)
    void clear() {
        m_queue.clear();
        m_flags = 0;
    }
    void update() {
        if (m_flags & 1) {
            m_queue.update();
            if (m_queue.empty()) {
                m_flags &= ~1;
            }
        }
    }
    bool isPlaying() const { return m_flags & 1; }
    unsigned char pad_8[0x20];
    CmdQueue<8, 0> m_queue;  // 0x28 (the name is not the original's)
    unsigned int m_flags;    // 0x978 bit 0: playing (the name is not the original's)
};
}  // namespace event

#endif

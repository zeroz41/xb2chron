#ifndef CLASSES_EVENT_SHAKER_H
#define CLASSES_EVENT_SHAKER_H

#include "classes/event/CmdQueue.h"

namespace event {
// table 0x7100B3D4D8
class Shaker {
public:
    virtual ~Shaker();  // slot 0
    // 1.0.0 has both out of line (0x71000ED8F8, 0x71000ED95C); 3.0.1 inlines them into ShakeManager::OnEventProc
    void stop();
    void tail();

    unsigned int m_flags;  // @0x8, stop() zeroes it; the name is not the original's
    unsigned char pad_0xc[0x334];
    CmdQueue<8, 0> m_cmdQueue;  // @0x340 (1.0.0's tail()); the name is not the original's
};
}  // namespace event

#endif

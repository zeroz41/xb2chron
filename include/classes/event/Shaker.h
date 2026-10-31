#ifndef CLASSES_EVENT_SHAKER_H
#define CLASSES_EVENT_SHAKER_H

#include "classes/event/CmdQueue.h"
#include "classes/event/ShakerRes.h"

namespace event {
// table 0x7100B3D4D8
class Shaker {
public:
    // inline: D2/D0 sit in CharaObj's tail; the table is weak
    virtual ~Shaker() {}  // slot 0
    // 1.0.0 has both out of line (0x71000ED8F8, 0x71000ED95C); 3.0.1 inlines them into ShakeManager::OnEventProc
    void stop();
    void tail();

    unsigned int m_flags;  // @0x8, stop() zeroes it; the name is not the original's
    unsigned char pad_0xc[0x4];
    ShakerRes m_res[8];  // @0x10, 0x60 each (the destructor tears them down); the name is not the original's
    unsigned char pad_0x310[0x30];
    CmdQueue<8, 0> m_cmdQueue;  // @0x340 (1.0.0's tail()); the name is not the original's
};
}  // namespace event

#endif

#ifndef CLASSES_EVENT_SHAKER_H
#define CLASSES_EVENT_SHAKER_H

#include "classes/event/CmdQueue.h"
#include "classes/event/ShakerRes.h"
#include "classes/event/ShakerUpdater.h"

namespace event {
// table 0x7100B3D4D8
class Shaker {
public:
    // inline: D2/D0 sit in CharaObj's tail; the table is weak
    virtual ~Shaker() {}  // slot 0
    // inline: ShakeManager's constructor builds it in place
    Shaker() : m_flags(0), pad_310(1), pad_318(0) {}
    // 1.0.0 has both out of line (0x71000ED8F8, 0x71000ED95C); 3.0.1 inlines them into ShakeManager::OnEventProc
    void stop();
    void tail();
    // ShakeManager's teardown (Manager's destructor) calls it (0x7100100540, 3.0.1 symbol)
    void destroy();

    unsigned int m_flags;  // @0x8, stop() zeroes it; the name is not the original's
    unsigned char pad_0xc[0x4];
    ShakerRes m_res[8];  // @0x10, 0x60 each (the destructor tears them down); the name is not the original's
    int pad_310;  // 0x310: the constructor sets 1
    unsigned int pad_314;
    long pad_318;  // 0x318: the constructor zeroes it
    unsigned char pad_320[0x18];
    ShakerUpdater::Update m_update;  // 0x338 (the name is not the original's)
    CmdQueue<8, 0> m_cmdQueue;  // @0x340 (1.0.0's tail()); the name is not the original's
};
}  // namespace event

#endif

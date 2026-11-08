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
    Shaker() : m_flags(0), m_resNum(1), m_cur(nullptr) {}
    // 1.0.0 has both out of line (0x71000ED8F8, 0x71000ED95C); 3.0.1 inlines them into ShakeManager::OnEventProc
    void stop();
    void tail();
    // ShakeManager's teardown (Manager's destructor) calls it (0x7100100540, 3.0.1 symbol)
    void destroy();
    void exec(float, float);
    // 1.0.0 has it out of line (0x71000EDA58, returning true); 3.0.1 inlines it into ShakeManager::play and
    // ShakeManager::idle: shakes with resource idx for time frames (none: until stopped), fading in and out over
    // fadeIn/fadeOut frames (the parameter names are not the original's)
    bool play(unsigned int idx, float time, float fadeIn, float fadeOut) {
        m_cur = &m_res[idx];
        if (time > 0.0f) {
            m_flags |= 3;
        } else {
            m_flags = (m_flags & ~3u) | 1;
        }
        m_frame = 0.0f;
        m_fadeInFrame = 0.0f;
        m_time = time;
        m_fadeIn = fadeIn;
        m_fadeOut = fadeOut;
        return true;
    }

    // 1.0.0 has it out of line (0x71000ED900); 3.0.1 inlines it into exec: the shake's strength, fading out over the
    // last m_fadeOut frames of a timed shake and in over its first m_fadeIn frames
    float getAlpha() const {
        if (m_fadeOut > 0.0f && (m_flags & 2) && m_time <= m_fadeOut) {
            return fmaxf(m_time - 1.0f, 0.0f) / m_fadeOut;
        }
        if (m_fadeIn > 0.0f && m_fadeInFrame < m_fadeIn) {
            return m_fadeInFrame / m_fadeIn;
        }
        return 1.0f;
    }

    // bit 0: shaking, bit 1: timed (m_time counts down); stop() zeroes it; the name is not the original's
    unsigned int m_flags;  // @0x8
    unsigned char pad_0xc[0x4];
    ShakerRes m_res[8];  // @0x10, 0x60 each (the destructor tears them down); the name is not the original's
    // 0x310: the resources in use; m_res[0] stays empty (the constructor sets 1, destroy keeps it); the name is not
    // the original's
    unsigned int m_resNum;
    unsigned int pad_314;
    ShakerRes* m_cur;  // 0x318: play's resource; the name is not the original's
    float m_frame;  // 0x320: the frame the shake has reached (update wraps it); the name is not the original's
    float m_fadeInFrame;  // 0x324: compared with m_fadeIn (getAlpha); the name is not the original's
    float m_time;  // 0x328: play's time left; the name is not the original's
    float m_fadeIn;  // 0x32c; the name is not the original's
    float m_fadeOut;  // 0x330; the name is not the original's
    unsigned int pad_334;
    ShakerUpdater::Update m_update;  // 0x338 (the name is not the original's)
    CmdQueue<8, 0> m_cmdQueue;  // @0x340 (1.0.0's tail()); the name is not the original's
};
}  // namespace event

#endif

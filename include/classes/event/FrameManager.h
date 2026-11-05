#ifndef CLASSES_EVENT_FRAMEMANAGER_H
#define CLASSES_EVENT_FRAMEMANAGER_H

#include <math.h>
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "classes/event/FrameInfo.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace gf { struct GF_PAUSE_HANDLE; }
namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3E1A8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::FrameManager>
class FrameManager : public IManager, public mm::mtl::Singleton<FrameManager> {
public:
    virtual ~FrameManager();  // slot 0
    // called by the evt_setup script plugin (application/BF2/ScriptPlayText); a result its callers ignore is declared void
    void addKeyFrame(float frame, bool);
    // what pauses the frame (evt_movie.play passes 11); the enumerators' names are unknown
    enum PAUSE_TYPE : int {};
    void pause(PAUSE_TYPE type, bool enable);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // out of line (mm::mtl::Singleton<event::FrameManager>::getPtr's static calls it)
    FrameManager();
    // the evt plugin's wait passes its frame count (1.0.0's evt wait calls it by this name)
    void setSkipAbleFrame(float frame);
    float getFrame() const;
    float getMaxFrame() const;
    // inline (1.0.0 had it out of line at 0x71000AA78C with no callers; FadeManager::update and OnEventProc inline
    // it): computes this frame's FrameInfo from the frame counters and the pause bits at 0x18
    const FrameInfo& frameInfo() {
        m_frameInfo.pad_0 = m_frame;
        float step = pad_164 - m_frame;
        if (pad_18 != 0) step = 0.0f;
        m_frameInfo.pad_4 = step;
        m_frameInfo.m_cmdStep = step;
        if ((pad_18 & 0x67f4) && step <= 0.0f) m_frameInfo.m_cmdStep = fmaxf(pad_188, 0.0f) + 1.0f;
        m_frameInfo.m_step = step;
        if (!(pad_10 & 1)) m_frameInfo.m_step = fmaxf(pad_188, 0.0f) + 1.0f;
        if (pad_18 & 0x38300a) m_frameInfo.m_step = 0.0f;
        m_frameInfo.pad_10 = pad_188;
        return m_frameInfo;
    }

private:
    // the fields below up to m_frame are set by the constructor; no reader seen yet
    int pad_10;
    int pad_14;

public:
    int pad_18;  // event::BgmManager's stop reads it: non-zero stops the BGM without a fade

private:
    unsigned char pad_1c[0x4];
    // each set to -1 (an invalid handle); the type is inferred: FrameManager::OnEventProc destroys pause handles
    gf::GF_PAUSE_HANDLE* pad_20[22];
    mm::mtl::FixStr<128> pad_d0;
    unsigned char pad_154[0x4];
    // what getFrame returns; the name is not the original's
    float m_frame;  // 0x158
    float pad_15c;
    float pad_160;
    float pad_164;
    unsigned char pad_168[0x4];
    int pad_16c;
    // what getMaxFrame returns; the name is not the original's
    float m_maxFrame;  // 0x170
    unsigned char pad_174[0xc];
    float m_skipAbleFrame;  // 0x180 setSkipAbleFrame stores its argument (the name is not the original's)
    int pad_184;
    float pad_188;  // 0x188 (frameInfo reads it)
    unsigned char pad_18c[0x4];
    // what addKeyFrame keeps sorted by frame (asserts `size() < capacity()`); the names are not the original's
    struct KeyFrame {
        float frame;
        bool flag;
    };
    mm::mtl::FixedVector<KeyFrame, 512> m_keyFrames;  // 0x190 (count at 0x1190)
    FrameInfo m_frameInfo;  // 0x1198: what frameInfo fills and returns (the name is not the original's)
};
}  // namespace event

#endif

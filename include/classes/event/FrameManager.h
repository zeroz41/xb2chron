#ifndef CLASSES_EVENT_FRAMEMANAGER_H
#define CLASSES_EVENT_FRAMEMANAGER_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
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

private:
    // the fields below up to m_frame are set by the constructor; no reader seen yet
    int pad_10;
    int pad_14;
    int pad_18;
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
    unsigned char pad_174[0x10];
    int pad_184;
    unsigned char pad_188[0x8];
    // what addKeyFrame keeps sorted by frame (asserts `size() < capacity()`); the names are not the original's
    struct KeyFrame {
        float frame;
        bool flag;
    };
    mm::mtl::FixedVector<KeyFrame, 512> m_keyFrames;  // 0x190 (count at 0x1190)
    long pad_1198;
    long pad_11a0;
    int pad_11a8;
};
}  // namespace event

#endif

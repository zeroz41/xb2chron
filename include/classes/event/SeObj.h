#ifndef CLASSES_EVENT_SEOBJ_H
#define CLASSES_EVENT_SEOBJ_H

#include "classes/event/AnmF32.h"
#include "event/CvType.h"
#include "gf/SoundHandle.h"
#include "mm/mtl/FixStr.h"

namespace event { class FrameInfo; }

namespace event {
// table 0x7100B3D408
// One sound effect SeManager plays by id. The layout follows play/exec/changeVolume/pan and the destructor; the
// field names are not the original's.
class SeObj {
public:
    // inline: SeManager's constructor builds the 32 slots in place
    SeObj() : m_flags(0) {}
    virtual ~SeObj();  // slot 0
    void exec(const FrameInfo& info);
    void draw(int, int, int);
    void play(const char* name, float wait, float fadeIn, float fadeOut, float volume);
    void changeVolume(float volume, float frame);  // 0x71000FE29C
    void pan(float pan, float frame, CV_TYPE type);  // 0x71000FE480

    // bit 0: in use (SeManager::changeVolume/pan forward only then); bit 1: ended; bit 2: held (the curves do not
    // advance); bit 3: a play time counts down; bit 4: fading in; bit 5: fading out; bit 6: volume curve; bit 7: pan
    // curve; bit 8: panned (the meanings are inferred from play/exec)
    unsigned int m_flags;  // 0x8
    gf::SoundHandle m_handle;  // 0xc play's SE
    mm::mtl::FixStr<64> m_name;  // 0x14 play's name (play restarts only for another name)
    float m_time;  // 0x58 time since play (exec adds the frame step)
    float m_wait;  // 0x5c play's second argument; exec counts it down and stops the SE at 0
    float m_fadeOutWait;  // 0x60 the same at first; the fade out runs over its last m_fadeOut frames
    float m_fadeIn;  // 0x64
    float m_fadeOut;  // 0x68
    float m_volume;  // 0x6c clamped to [0, 1]
    AnmF32 m_volumeAnm;  // 0x70 changeVolume's curve
    float m_pan;  // 0x180
    AnmF32 m_panAnm;  // 0x188 pan's curve
};
}  // namespace event

#endif

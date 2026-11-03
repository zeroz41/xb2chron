#ifndef CLASSES_EVENT_CHARAEFFECTPLAYER_H
#define CLASSES_EVENT_CHARAEFFECTPLAYER_H

#include "classes/event/AnmF32.h"

namespace mm { class Vec3; }

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3CA98
class CharaEffectPlayer {
public:
    virtual ~CharaEffectPlayer();  // slot 0
    // the volume fade's kind (the evt_chara script commands pass 1); no enumerator is named
    enum VF_TYPE : int {};
    void playVolumeFade(VF_TYPE type, int a, const mm::Vec3& b, const mm::Vec3& c, float d, float e, int f, float g);
    void playVolumeFadeAnim(VF_TYPE type, float time, float delay);
    void stopVolumeFade(VF_TYPE type);
    void playRimBloom(int type);
    void stopRimBloom();
    void stopAfterImage();

    // bit 3: an after image is on (stopAfterImage releases it); the name is not the original's
    unsigned int m_flags;  // 0x8
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10, -1 when none; the name is not the original's
    unsigned char pad_18[0x68];
    // the two curves the destructor tears down (last first); the names are not the original's
    AnmF32 m_anm0;  // 0x80
    AnmF32 m_anm1;  // 0x190
};
}  // namespace event

#endif

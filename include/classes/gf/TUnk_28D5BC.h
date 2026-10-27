#ifndef CLASSES_GF_TUNK_28D5BC_H
#define CLASSES_GF_TUNK_28D5BC_H

#include "classes/gf/GfSound.h"
#include "gf/SoundHandle.h"

namespace fw { class UpdateInfo; }

namespace gf {

// a class with no table (named after its constructor 0x710028D5BC): the 0x20-byte object TUnk_B535D0's setup
// fn_7100291100 makes (gf_game_arena.cpp line 112) and keeps at +0xD0. It plays one BGM after a delay under its
// own sound category handle.
class TUnk_28D5BC {
public:
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them; their code is in GfAppendWire's unit
    // range. fn_710028D5BC is the constructor; fn_710028D5F0: the arena's setup calls it last on this object; it
    // calls gf::GfSound::createCategoryHandle.
    TUnk_28D5BC();
    void fn_710028D5F0();
    // fn_710028D5EC (placeholder code address; TUnk_B535D0::fn_7100291B64 runs it before freeing the object)
    ~TUnk_28D5BC();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: their code is next to the
    // constructor. TUnk_B535D0::fn_7100291B64 calls fn_710028D624 before deleting the object; TUnk_B535D0::fn_7100292060
    // calls fn_710028D644 each frame with the frame's update info. fn_710028D624 releases m_category;
    // fn_710028D644 counts m_delay down by the frame's time, then plays m_bgm (GfSound::playBgm with m_fadeTime,
    // category 3) and, once that BGM stops playing, runs stop().
    void fn_710028D624();
    void fn_710028D644(const ::fw::UpdateInfo& info);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (no caller in the code). A member: its code
    // is next to the constructor and works on this object's fields. What it does: unless a BGM is playing, keeps the
    // BGM ID, its fade time and the delay (+0.001) for fn_710028D644 and sets m_category's volume of category 1 to 0
    // over 1 second.
    void fn_710028D738(unsigned int bgm, float fadeTime, float delay);
    // stops the BGM: category 1 back to full volume, GfSound::stopBgm over 1 second, the handle cleared (inline:
    // fn_710028D644 and TUnk_B52C38::fn_710028D4A4 hold copies; the name is not the original's)
    void stop() {
        if (GfSound* sound = GfSound::get()) {
            m_delay = 0.0f;
            m_bgm = 0;
            sound->setCategoryVolume(m_category, static_cast<fw::SoundCategory>(1), 1.0f, 1.0f);
            sound->stopBgm(m_handle, 1.0f);
            m_handle.clear();
        }
    }

    SoundHandle m_handle;  // GfSound::playBgm's (the name is not the original's)
    GF_SE_CATEGORY_HANDLE* m_category;  // GfSound::createCategoryHandle's; -1 before (the name is not the original's)
    float m_delay;  // time left before m_bgm plays (the name is not the original's)
    float m_fadeTime;  // playBgm's time (the name is not the original's)
    unsigned int m_bgm;  // playBgm's ID (the name is not the original's)
    unsigned char pad_1C[0x4];
};

}  // namespace gf

#endif

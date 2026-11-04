#ifndef CLASSES_GF_TUNK_28D5BC_H
#define CLASSES_GF_TUNK_28D5BC_H

#include "classes/gf/GfSound.h"
#include "gf/SoundHandle.h"

namespace fw { class UpdateInfo; }

namespace gf {

// a class with no table (named after its constructor 0x710028D5BC): the 0x20-byte object GfGameArena's setup
// initialize makes (gf_game_arena.cpp line 112) and keeps at +0xD0. It plays one BGM after a delay under its
// own sound category handle.
class GfArenaJingle {
public:
    // 2.0.0's symbols name them. fn_710028D5BC is the constructor; initialize: the arena's setup calls it last on this
    // object; it calls gf::GfSound::createCategoryHandle.
    GfArenaJingle();
    void initialize();
    // fn_710028D5EC (placeholder code address; GfGameArena::finalize runs it before freeing the object)
    ~GfArenaJingle();
    // 2.0.0's symbols name them. Their code is next to the constructor. GfGameArena::finalize calls finalize before
    // deleting the object; GfGameArena::update calls update each frame with the frame's update info. finalize releases
    // m_category; update counts m_delay down by the frame's time, then plays m_bgm (GfSound::playBgm with m_fadeTime,
    // category 3) and, once that BGM stops playing, runs stop().
    void finalize();
    void update(const ::fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: unless a BGM is playing, keeps the BGM ID, its fade time and the delay
    // (+0.001) for update and sets m_category's volume of category 1 to 0 over 1 second.
    void playJingle(unsigned int bgm, float fadeTime, float delay);
    // stops the BGM: category 1 back to full volume, GfSound::stopBgm over 1 second, the handle cleared (inline:
    // update and GfArenaBattle::mapjumpForReturnField hold copies; the name is not the original's)
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

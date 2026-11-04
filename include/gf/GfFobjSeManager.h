#ifndef GF_GFFOBJSEMANAGER_H
#define GF_GFFOBJSEMANAGER_H

#include "mm/mtl/Vector.h"
#include "mm/mtl/Map.h"

namespace fw { class SoundPack; }

namespace gf {
// the sounds of drop items (functions, by its symbols); GfFobjManager keeps one at 0x90D0
class GfFobjSeManager {
public:
    // GfFobjManager::initialize fills it from the table 0x7B, member 0: row 0x44's float, row 0x45's 16 bits
    // (the names are not the original's); the constructor's and dispose's values are 0.1 and 8
    struct CreateInfo {
        CreateInfo() : m_interval(0.1f), m_maxSe(8) {}
        // createSe plays a sound again only after this long since it last played (its Map's times)
        float m_interval;
        unsigned int m_maxSe;  // create reserves room for this many playing sounds
    };
    // a playing sound (Vector<SeInfo>::erase, by its symbols; update asks SoundManager::isPlaying for the word at 4)
    struct SeInfo {
        unsigned int pad_0x0;
        unsigned int m_soundId;  // the name is not the original's
    };

    GfFobjSeManager(const CreateInfo* info);
    // no copy in the module: GfFobjManager's destructor has it inline
    ~GfFobjSeManager() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    void update(float deltaTime);
    void createSe(unsigned short se);
    // 2.0.0's symbols name it. What it does: looks the drop items' sound pack up again (fw::SoundManager::findPack of
    // getSePackName's name, as create does) into m_pack.
    void rebuildForGameType();

    CreateInfo m_info;  // create's copy (the name is not the original's)
    fw::SoundPack* m_pack;  // SoundManager::findPack's (the name is not the original's)
    mm::mtl::Vector<SeInfo> m_seInfos;  // the name is not the original's
    mm::mtl::Map<unsigned short, float> m_seTimes;  // update adds each frame's time step (not the original's name)
};
}  // namespace gf

#endif

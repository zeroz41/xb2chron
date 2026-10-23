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
    // (the names are not the original's)
    struct CreateInfo {
        unsigned int m_param0;
        unsigned int m_param1;
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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because GfFobjManager::
    // fn_7100289668 passes its GfFobjSeManager (this + 0x90D0). What it does: looks the drop items' sound pack up again
    // (fw::SoundManager::findPack of fn_710027C7D4's name, as create does) into m_pack.
    void fn_7100282EA8();

    unsigned char pad_0x0[0x8];
    fw::SoundPack* m_pack;  // SoundManager::findPack's (the name is not the original's)
    mm::mtl::Vector<SeInfo> m_seInfos;  // the name is not the original's
    mm::mtl::Map<unsigned short, float> m_seTimes;  // update adds each frame's time step (not the original's name)
};
}  // namespace gf

#endif

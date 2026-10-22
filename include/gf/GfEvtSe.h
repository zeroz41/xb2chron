#ifndef GF_GFEVTSE_H
#define GF_GFEVTSE_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class SoundPack; }
namespace fw { class SoundResource; }

namespace gf {
// an event's sound effects (no table): createSe requests sound/se/<name>.xsp, isLoadedSe waits for them,
// destroySe releases them
class GfEvtSe {
public:
    // one requested SE (0x38 bytes); the name is not the original's
    struct SeInfo {
        fw::SoundResource* m_resource;  // what SoundResource::request returned, released by destroySe
        fw::SoundPack* m_pack;  // 1.0.0's update finds it with SoundManager::findPack once the resource has loaded
        mm::mtl::FixStr<32> m_name;  // the name createSe was given
    };

    GfEvtSe();
    ~GfEvtSe();
    void cleanup();
    void destroySe();
    void createSe(const char* name);
    bool isLoadedSe() const;

    mm::mtl::FixedVector<SeInfo, 8> m_ses;  // the name is not the original's
    bool m_isCleanup;  // cleanup sets it; the name is not the original's
};
}  // namespace gf

#endif

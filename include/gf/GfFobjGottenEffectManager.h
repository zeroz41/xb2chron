#ifndef GF_GFFOBJGOTTENEFFECTMANAGER_H
#define GF_GFFOBJGOTTENEFFECTMANAGER_H

#include "mm/mtl/Vector.h"

namespace gf {
// the effects of gotten drop items (functions, by its symbols); GfFobjManager keeps one at 0x9088
class GfFobjGottenEffectManager {
public:
    struct CreateInfo {
        int m_capacity;  // GfFobjManager::initialize passes 0x20 (the name is not the original's)
    };
    // an effect followed (Vector<EffectInfo>::erase, by its symbols, steps 0x60 bytes)
    struct EffectInfo {
        unsigned char pad_0x0[0x60];
    };

    GfFobjGottenEffectManager(const CreateInfo* info);
    // no copy in the module: GfFobjManager's destructor has it inline
    ~GfFobjGottenEffectManager() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    void update(float deltaTime);

    unsigned char pad_0x0[0x20];
    mm::mtl::Vector<EffectInfo> m_effects;  // the name is not the original's
};
}  // namespace gf

#endif

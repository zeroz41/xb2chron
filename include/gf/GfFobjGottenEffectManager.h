#ifndef GF_GFFOBJGOTTENEFFECTMANAGER_H
#define GF_GFFOBJGOTTENEFFECTMANAGER_H

#include "mm/mtl/Vector.h"
#include "mm/Vec3.h"

namespace gf {
// the effects of gotten drop items (functions, by its symbols); GfFobjManager keeps one at 0x9088
class GfFobjGottenEffectManager {
public:
    struct CreateInfo {
        CreateInfo() : m_capacity(0) {}
        unsigned int m_capacity;  // GfFobjManager::initialize passes 0x20 (the name is not the original's)
    };
    // an effect followed (Vector<EffectInfo>::erase, by its symbols, steps 0x60 bytes)
    // (Vector<EffectInfo>::push_back copies four Vec3s, then the words at 0x40, 0x48 and 0x50; the names are not
    // the original's)
    struct EffectInfo {
        mm::Vec3 m_pos;
        unsigned char pad_0x10[0x30];
        unsigned int m_handle;  // EffectManager's handle: dispose kills it
        unsigned char pad_0x44[0x1c];
    };

    GfFobjGottenEffectManager(const CreateInfo* info);
    // no copy in the module: GfFobjManager's destructor has it inline
    ~GfFobjGottenEffectManager() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    void update(float deltaTime);
    struct CreateEffectInfo;
    void createEffect(const CreateEffectInfo& info);

    CreateInfo m_info;  // create's copy (the name is not the original's)
    // EffectManager::search's results for cmn_200_030, cmn_200_031 and cmn_200_032 (createEffect picks one by its
    // info's byte at 0x18; the name is not the original's)
    void* m_effectRes[3];
    mm::mtl::Vector<EffectInfo> m_effects;  // the name is not the original's
};
}  // namespace gf

#endif

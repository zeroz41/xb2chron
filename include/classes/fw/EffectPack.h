#ifndef CLASSES_FW_EFFECTPACK_H
#define CLASSES_FW_EFFECTPACK_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixStr.h"

namespace fw {
// table 0x7100B41628; counted (gf::MapEff::destroy releases the one it keeps, asserting reference_object.h's
// `m_RefCount > 0`)
class EffectPack : public ::mm::mtl::ReferenceObject {
public:
    // the pack's effect resource (efb) by name, null when it has none
    void* searchEfb(const char* name) const;
    virtual ~EffectPack();  // slot 0
    // a pack made from a resource in memory (gf::MapEff::create passes the map's effect asset)
    static EffectPack* createFromMemory(void* data, unsigned int size, const char* name, bool flag);

    unsigned char pad_c[0x4C];
    // the name fw::EffectManager files the pack under (addPack/removePack key its pack map with it; createFromMemory
    // makes it "<name>+<data address>"; the field name is not the original's). sizeof(EffectPack) is 0xE0
    // (createFromMemory's allocation)
    mm::mtl::FixStr<128> m_name;
    unsigned char pad_dc[0x4];
};
}  // namespace fw

#endif

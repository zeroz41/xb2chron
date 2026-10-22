#ifndef CLASSES_FW_EFFECTPACK_H
#define CLASSES_FW_EFFECTPACK_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace fw {
// table 0x7100B41628; counted (gf::MapEff::destroy releases the one it keeps, asserting reference_object.h's
// `m_RefCount > 0`)
class EffectPack : public ::mm::mtl::ReferenceObject {
public:
    virtual ~EffectPack();  // slot 0
    // a pack made from a resource in memory (gf::MapEff::create passes the map's effect asset)
    static EffectPack* createFromMemory(void* data, unsigned int size, const char* name, bool flag);
};
}  // namespace fw

#endif

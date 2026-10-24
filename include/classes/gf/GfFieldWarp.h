#ifndef CLASSES_GF_GFFIELDWARP_H
#define CLASSES_GF_GFFIELDWARP_H

#include "classes/gf/AFieldSeq.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfAllocator.h"

namespace gf {
// table 0x7100B523F8; the base at 0x28 is mm::mtl::PtrSingleton<gf::GfFieldWarp> (its destructor stores that table and
// clears the instance)
class GfFieldWarp : public ::gf::AFieldSeq, public ::mm::mtl::PtrSingleton< ::gf::GfFieldWarp> {
public:
    // inline: 3.0.1 has no copy of it (GfFieldManager::initialize inlines it)
    GfFieldWarp(const GfSetupParam& param) : AFieldSeq(param) {}
    // GfFieldManager::initialize's (inline in gf_field_map_gimmick.h, which its allocation cites; the name is not the
    // original's)
    static void build(const GfSetupParam& param) {
#line 458 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/field/gf_field_map_gimmick.h"
        new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldWarp(param);
    }
    virtual const char* getIdStr() const {  // slot 0
        static const char s_classId[] = "GfFieldWarp";
        return s_classId;
    }
    virtual ~GfFieldWarp() {}  // slot 5
    virtual void onFsSucceeded();  // slot 7
};
}  // namespace gf

#endif

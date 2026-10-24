#ifndef CLASSES_GF_GFFIELDJUMP_H
#define CLASSES_GF_GFFIELDJUMP_H

#include "classes/gf/AFieldSeq.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfAllocator.h"

namespace gf {
// table 0x7100B52380; the base at 0x28 is mm::mtl::PtrSingleton<gf::GfFieldJump> (its destructor stores that table and
// clears the instance)
class GfFieldJump : public ::gf::AFieldSeq, public ::mm::mtl::PtrSingleton< ::gf::GfFieldJump> {
public:
    // inline: 3.0.1 has no copy of it (GfFieldManager::initialize inlines it)
    GfFieldJump(const GfSetupParam& param) : AFieldSeq(param) {}
    // GfFieldManager::initialize's (inline in gf_field_map_gimmick.h, which its allocation cites; the name is not the
    // original's)
    static void build(const GfSetupParam& param) {
#line 403 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/field/gf_field_map_gimmick.h"
        new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldJump(param);
    }
    virtual const char* getIdStr() const {  // slot 0
        static const char s_classId[] = "GfFieldJump";
        return s_classId;
    }
    virtual ~GfFieldJump() {}  // slot 5
    virtual void onFsSucceeded();  // slot 7
};
}  // namespace gf

#endif

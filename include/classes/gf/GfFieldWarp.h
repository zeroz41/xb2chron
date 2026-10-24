#ifndef CLASSES_GF_GFFIELDWARP_H
#define CLASSES_GF_GFFIELDWARP_H

#include "classes/gf/AFieldSeq.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf {
// table 0x7100B523F8; the base at 0x28 is mm::mtl::PtrSingleton<gf::GfFieldWarp> (its destructor stores that table and
// clears the instance)
class GfFieldWarp : public ::gf::AFieldSeq, public ::mm::mtl::PtrSingleton< ::gf::GfFieldWarp> {
public:
    virtual const char* getIdStr() const {  // slot 0
        static const char s_classId[] = "GfFieldWarp";
        return s_classId;
    }
    virtual ~GfFieldWarp() {}  // slot 5
    virtual void onFsSucceeded();  // slot 7
};
}  // namespace gf

#endif

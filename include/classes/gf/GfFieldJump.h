#ifndef CLASSES_GF_GFFIELDJUMP_H
#define CLASSES_GF_GFFIELDJUMP_H

#include "classes/gf/AFieldSeq.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf {
// table 0x7100B52380; the base at 0x28 is mm::mtl::PtrSingleton<gf::GfFieldJump> (its destructor stores that table and
// clears the instance)
class GfFieldJump : public ::gf::AFieldSeq, public ::mm::mtl::PtrSingleton< ::gf::GfFieldJump> {
public:
    virtual const char* getIdStr() const {  // slot 0
        static const char s_classId[] = "GfFieldJump";
        return s_classId;
    }
    virtual ~GfFieldJump() {}  // slot 5
    virtual void onFsSucceeded();  // slot 7
};
}  // namespace gf

#endif

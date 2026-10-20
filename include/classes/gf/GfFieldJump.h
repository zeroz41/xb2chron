#ifndef CLASSES_GF_GFFIELDJUMP_H
#define CLASSES_GF_GFFIELDJUMP_H

#include "classes/gf/AFieldSeq.h"

namespace gf {
// a base of gf::GfFieldJump no evidence names yet
class TUnk_B523D8 {
public:
    virtual ~TUnk_B523D8();
};
// table 0x7100B52380; base at 0x28 unknown (TUnk_B523D8)
class GfFieldJump : public ::gf::AFieldSeq, public TUnk_B523D8 {
public:
    virtual void getIdStr() const;  // slot 0
    virtual ~GfFieldJump();  // slot 5
    virtual void onFsSucceeded();  // slot 7
};
}  // namespace gf

#endif

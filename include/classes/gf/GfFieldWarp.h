#ifndef CLASSES_GF_GFFIELDWARP_H
#define CLASSES_GF_GFFIELDWARP_H

#include "classes/gf/AFieldSeq.h"

namespace gf {
// a base of gf::GfFieldWarp no evidence names yet
class TUnk_B52450 {
public:
    virtual ~TUnk_B52450();
};
// table 0x7100B523F8; base at 0x28 unknown (TUnk_B52450)
class GfFieldWarp : public ::gf::AFieldSeq, public TUnk_B52450 {
public:
    virtual void getIdStr() const;  // slot 0
    virtual ~GfFieldWarp();  // slot 5
    virtual void onFsSucceeded();  // slot 7
};
}  // namespace gf

#endif

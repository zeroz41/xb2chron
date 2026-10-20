// not proven yet: its table differs from the original's (word 7: _ZN2gf18GfMenuObjCommonJog11reloadParamEv where the original has _ZN2gf12GfMenuObject11reloadParamEv)
#ifndef CLASSES_GF_GFMENUOBJCOMMONJOG_H
#define CLASSES_GF_GFMENUOBJCOMMONJOG_H

#include "classes/gf/GfMenuObjCommonList.h"

namespace gf {
// table 0x7100B61408
class GfMenuObjCommonJog : public ::gf::GfMenuObjCommonList {
public:
    virtual void initialize();  // slot 2
    virtual void reloadParam();  // slot 5
    virtual void eventHudSceneChange(unsigned int);  // slot 6
};
}  // namespace gf

#endif

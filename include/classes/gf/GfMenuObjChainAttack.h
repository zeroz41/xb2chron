#ifndef CLASSES_GF_GFMENUOBJCHAINATTACK_H
#define CLASSES_GF_GFMENUOBJCHAINATTACK_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// a base of gf::GfMenuObjChainAttack no evidence names yet
class TUnk_B60C10 {
public:
    virtual void isEnableSelect(unsigned int, int) = 0;
};
// table 0x7100B60BC0; base at 0x28 unknown (TUnk_B60C10)
class GfMenuObjChainAttack : public ::gf::GfMenuObject, public TUnk_B60C10 {
public:
    class ExtendListener;
    class FullBurstListener;
    class ResultListener;
    class StartListener;
    class StatusListener;
    virtual ~GfMenuObjChainAttack();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    virtual void isEnableSelect(unsigned int, int);  // slot 7
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJDAMAGEBUFF_H
#define CLASSES_GF_GFMENUOBJDAMAGEBUFF_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61760
class GfMenuObjDamageBuff : public ::gf::GfMenuObject {
public:
    class DamageInfo;
    class ListListener;
    virtual ~GfMenuObjDamageBuff();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJDAMAGEVALUE_H
#define CLASSES_GF_GFMENUOBJDAMAGEVALUE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61808
class GfMenuObjDamageValue : public ::gf::GfMenuObject {
public:
    class DamageInfo;
    class ListListener;
    virtual ~GfMenuObjDamageValue();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

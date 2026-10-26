#ifndef CLASSES_GF_GFMENUOBJDAMAGEBUFF_H
#define CLASSES_GF_GFMENUOBJDAMAGEBUFF_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61760
class GfMenuObjDamageBuff : public ::gf::GfMenuObject {
public:
    class DamageInfo;
    class ListListener;
    static void closeAll();  // GfMenuManager::gevSalvageStateChange(6) calls it (1.0.0 symbol)
    virtual ~GfMenuObjDamageBuff();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

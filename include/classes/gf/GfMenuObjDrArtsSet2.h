#ifndef CLASSES_GF_GFMENUOBJDRARTSSET2_H
#define CLASSES_GF_GFMENUOBJDRARTSSET2_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61978
class GfMenuObjDrArtsSet2 : public ::gf::GfMenuObject {
public:
    class ArtsListListener;
    class LevelupListener;
    class MainListener;
    class WpnTypeListener;
    virtual ~GfMenuObjDrArtsSet2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

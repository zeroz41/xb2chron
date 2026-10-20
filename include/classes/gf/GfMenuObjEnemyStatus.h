#ifndef CLASSES_GF_GFMENUOBJENEMYSTATUS_H
#define CLASSES_GF_GFMENUOBJENEMYSTATUS_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61CD0
class GfMenuObjEnemyStatus : public ::gf::GfMenuObject {
public:
    class ElemListener;
    class MainListener;
    virtual ~GfMenuObjEnemyStatus();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

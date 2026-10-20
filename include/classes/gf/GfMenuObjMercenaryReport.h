#ifndef CLASSES_GF_GFMENUOBJMERCENARYREPORT_H
#define CLASSES_GF_GFMENUOBJMERCENARYREPORT_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63500
class GfMenuObjMercenaryReport : public ::gf::GfMenuObject {
public:
    class MainListener;
    class RewardListener;
    virtual ~GfMenuObjMercenaryReport();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

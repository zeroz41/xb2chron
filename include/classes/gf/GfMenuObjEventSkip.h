#ifndef CLASSES_GF_GFMENUOBJEVENTSKIP_H
#define CLASSES_GF_GFMENUOBJEVENTSKIP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61F60
class GfMenuObjEventSkip : public ::gf::GfMenuObject {
public:
    class ListListener;
    virtual ~GfMenuObjEventSkip();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

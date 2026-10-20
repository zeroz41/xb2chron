#ifndef CLASSES_GF_GFMENUOBJEVENTSUBTITLE_H
#define CLASSES_GF_GFMENUOBJEVENTSUBTITLE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61FD0
class GfMenuObjEventSubtitle : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjEventSubtitle();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

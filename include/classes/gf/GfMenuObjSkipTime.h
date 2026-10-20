#ifndef CLASSES_GF_GFMENUOBJSKIPTIME_H
#define CLASSES_GF_GFMENUOBJSKIPTIME_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64960
class GfMenuObjSkipTime : public ::gf::GfMenuObject {
public:
    class MainListener;
    class TimeChangeListener;
    virtual ~GfMenuObjSkipTime();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

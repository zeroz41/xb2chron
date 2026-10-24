#ifndef CLASSES_GF_GFMENUOBJPARTYSTATUS_H
#define CLASSES_GF_GFMENUOBJPARTYSTATUS_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63FF0
class GfMenuObjPartyStatus : public ::gf::GfMenuObject {
public:
    static void open(bool flag);  // 1.0.0 symbol
    static void close(bool flag);  // 1.0.0 symbol
    static void lock(bool lock);  // 1.0.0 symbol (GfMenuReference::clearPartyStatusLock calls it)
    class ComboReqListener;
    class MainListener;
    virtual ~GfMenuObjPartyStatus();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

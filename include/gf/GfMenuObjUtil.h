#ifndef GF_GFMENUOBJUTIL_H
#define GF_GFMENUOBJUTIL_H

namespace gf { class GfMenuCallContext; }

namespace gf {
// the menu objects' shared helpers; its functions take no object
class GfMenuObjUtil {
public:
    static bool checkCCStart(GfMenuCallContext* context);  // a context that is not running yet
};
}  // namespace gf

#endif

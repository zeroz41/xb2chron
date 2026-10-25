#ifndef CLASSES_GF_GFMENUOBJFIELDICON_H
#define CLASSES_GF_GFMENUOBJFIELDICON_H

#include "classes/gf/GfMenuObject.h"
#include "mm/Vec3.h"

namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B62330
class GfMenuObjFieldIcon : public ::gf::GfMenuObject {
public:
    // what open shows (the field names are not the original's): the icon (GfMenuBdat::getIconImageIndex's; 0 for
    // none) at a world point, its position plus an offset
    struct OpenParam {
        int m_icon;
        mm::Vec3 m_pos;
        mm::Vec3 m_offset;
    };
    GfMenuObjFieldIcon(unsigned int handle);
    virtual ~GfMenuObjFieldIcon();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void open(GfMenuCallContext* context, const OpenParam& param);
    static void close(GfMenuCallContext* context);
    static void disp(GfMenuCallContext* context, bool disp);
    static void dispAll(bool disp);
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJNAMESELECT_H
#define CLASSES_GF_GFMENUOBJNAMESELECT_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B639B8
class GfMenuObjNameSelect : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjNameSelect(unsigned int handle);
    virtual ~GfMenuObjNameSelect();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    unsigned char pad_24[4];
    // the constructor creates it, the destructor releases it: the context the confirmation text (GfMenuObjCommonText)
    // runs on
    GfMenuCallContext* m_context;
};
}  // namespace gf

#endif

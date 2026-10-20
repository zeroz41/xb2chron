#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B5FF10
class GfMenuObjBladeCreate : public ::gf::GfMenuObject {
public:
    class BoosterNumListener;
    class BoosterSelectListener;
    class ConfirmListener;
    class CreationListener;
    class CrystalSelectListener;
    class DriverSelectListener;
    class IdeagramListener;
    class MainListener;
    class ResultListener;
    virtual ~GfMenuObjBladeCreate();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

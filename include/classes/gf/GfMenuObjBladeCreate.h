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
    // what registOpenParam keeps for the next open (ScriptPlayText's ui openBladeCreate passes its script
    // argument); the name is not the original's
    struct OpenParam {
        unsigned int m_value;
    };
    static void registOpenParam(const OpenParam& param);
    virtual ~GfMenuObjBladeCreate();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

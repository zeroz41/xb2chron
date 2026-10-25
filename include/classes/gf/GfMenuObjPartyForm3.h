#ifndef CLASSES_GF_GFMENUOBJPARTYFORM3_H
#define CLASSES_GF_GFMENUOBJPARTYFORM3_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63E48
class GfMenuObjPartyForm3 : public ::gf::GfMenuObject {
public:
    class BGListener;
    class DriverSelectListener;
    class MainListener;
    // what registOpenParam keeps for the next open (ScriptPlayText's ui settingPartyFormBeforeBattle passes 1);
    // the name is not the original's
    struct OpenParam {
        unsigned short m_value;
    };
    static void registOpenParam(const OpenParam& param);
    virtual ~GfMenuObjPartyForm3();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJTITLE_H
#define CLASSES_GF_GFMENUOBJTITLE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64D38
class GfMenuObjTitle : public ::gf::GfMenuObject {
public:
    // TitleMenu::setupTitle attaches the title menu object to its call context
    static void attach(GfMenuCallContext* context);
    virtual ~GfMenuObjTitle();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

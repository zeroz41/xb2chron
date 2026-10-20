#ifndef CLASSES_GF_GFMENUOBJTARGETINFO_H
#define CLASSES_GF_GFMENUOBJTARGETINFO_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64BD8
class GfMenuObjTargetInfo : public ::gf::GfMenuObject {
public:
    class EnemyListener;
    class OtherListener;
    class SymbolListener;
    virtual ~GfMenuObjTargetInfo();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

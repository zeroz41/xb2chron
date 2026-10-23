#ifndef CLASSES_GF_GFMENUOBJBLKIZUNARING_H
#define CLASSES_GF_GFMENUOBJBLKIZUNARING_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B604F8
class GfMenuObjBlKizunaRing : public ::gf::GfMenuObject {
public:
    class BladeSkillInfoListener;
    class MainListener;
    class RingListener;
    class RingPadListener;
    class SkillDetailListener;
    virtual ~GfMenuObjBlKizunaRing();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static bool attach(GfMenuCallContext* context);  // opens the ring on that call context (false: it did not)
};
}  // namespace gf

#endif

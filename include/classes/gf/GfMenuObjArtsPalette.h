#ifndef CLASSES_GF_GFMENUOBJARTSPALETTE_H
#define CLASSES_GF_GFMENUOBJARTSPALETTE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B5FAF8
class GfMenuObjArtsPalette : public ::gf::GfMenuObject {
public:
    static void reverse(bool reverse);
    // 1.0.0 symbol (GfMenuReference::setReversePaletteBtnState calls it with the slot; the parameter name is not
    // the original's)
    static void pushReverseBtn(unsigned int slot);  // 1.0.0 symbol (GfMenuReference::setPaletteModeReverse calls it)
    // what GfMenuObjChainAttack::openStatus and closeStatus call when a chain attack's status opens and closes
    static void startChainAttack();
    static void exitChainAttack();
    class MainListener;
    class ReverseListener;
    virtual ~GfMenuObjArtsPalette();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif

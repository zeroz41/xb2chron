#ifndef CLASSES_GMK_GMKDMGSE_H
#define CLASSES_GMK_GMKDMGSE_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantom.h"

namespace gmk {
// table 0x7100B6E240
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkDmgSe : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    GmkDmgSe() {}  // inline: construct_n<GmkDmgSe> constructs in place with these stores
    virtual ~GmkDmgSe();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void dispose();  // slot 5
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x33);
    // 0x48..0x50: padding before the 16-aligned phantom
    GmkPhantom m_phantom;  // 0x50 (the name is not the original's)
    // the constructor sets them (meaning unknown)
    bool pad_e0 = false;
    float pad_e4 = 0.0f;
    float pad_e8 = 1.0f;
    // 0xec..0xf0: tail padding (size 0xf0, TGmkList::getInst's stride; Vector<GmkDmgSe>::expand copies 0xe0..0xec)
};
}  // namespace gmk

#endif

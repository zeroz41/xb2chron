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
    unsigned char pad_48[0x8];
    GmkPhantom m_phantom;  // 0x50 (the name is not the original's)
    unsigned char pad_d8[0x8];
    // the constructor sets them (meaning unknown)
    bool pad_e0 = false;
    float pad_e4 = 0.0f;
    float pad_e8 = 1.0f;
    unsigned char pad_ec[0x4];  // size from TGmkList::getInst's stride (0xf0)
};
}  // namespace gmk

#endif

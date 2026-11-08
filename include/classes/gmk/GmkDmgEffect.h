#ifndef CLASSES_GMK_GMKDMGEFFECT_H
#define CLASSES_GMK_GMKDMGEFFECT_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6E1D8
class GmkDmgEffect : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    GmkDmgEffect() {}  // inline, user-provided: the defaults are stored by Vector<T>::resize/extend, no zero fill
    virtual ~GmkDmgEffect();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    // 2.0.0's symbols name it
    void applyEffectParam() const;
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x32);
    unsigned char pad_48 = 1;
    unsigned char pad_49[0x3];
    unsigned int m_effectHandle = 0;  // dispose removes it from fw::EffectManager (the name is not the original's)  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif

#ifndef CLASSES_GMK_GMKEFFECT_H
#define CLASSES_GMK_GMKEFFECT_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkEffectGobCustom; }

namespace gmk {
// table 0x7100B6C550
class GmkEffect : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    virtual ~GmkEffect();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void debugUpdateMmf();  // slot 10
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(13);
    unsigned char pad_48[0x48];
    void* pad_90;  // dispose clears 0x90..0xa8
    void* pad_98;
    void* pad_a0;
    unsigned char pad_a8[0x4];
    unsigned m_effectHandle;  // 0xac: the playing effect (dispose removes it from EffectManager; the name is not the original's)
    unsigned char pad_b0[0x8];
    unsigned long m_flags;  // 0xb8: dispose clears its low 3 bits (the name is not the original's)
    unsigned char pad_c0[0x8];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif

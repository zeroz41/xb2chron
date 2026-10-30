#ifndef CLASSES_GMK_GMKTRIGGER_H
#define CLASSES_GMK_GMKTRIGGER_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantom.h"

namespace gmk {
// table 0x7100B6D1D0
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkTrigger : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize (0x71005D9608 allocates count bytes); the fields are not read yet
    class BdatInfo {
    public:
        BdatInfo() {}  // user-provided: Vector<BdatInfo>::resize/extend leave the byte as it is (no zero fill)
        unsigned char pad_0[0x1];
    };
    // user-provided: construct_n<GmkTrigger> stores the defaults below only (no zero fill of the element first)
    GmkTrigger() {}
    virtual ~GmkTrigger();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    void seqWaitToValidLinkGmkList(float dt);
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x34);
    // 0x48..0x50: padding (copy_construct_n<gmk::GmkTrigger> copies nothing there)
    GmkPhantom m_phantom;  // 0x50: the destructor destroys it, dispose disposes it (the name is not the original's)
    // the step update runs: create sets it to seqWaitToValidLinkGmkList (symbol), update calls it, dispose clears it.
    // A member function pointer: copy_construct_n<gmk::GmkTrigger> copies its two words apart (fields: size from
    // TGmkList::getInst's stride)
    void (GmkTrigger::*m_seq)(float dt) = nullptr;
};
}  // namespace gmk

#endif

#ifndef CLASSES_GMK_GMKSALVAGELOCATOR_H
#define CLASSES_GMK_GMKSALVAGELOCATOR_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
#include "gf/GfDropitemEmitter.h"

namespace gmk {
// table 0x7100B6CAA0
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkSalvageLocator : public ::gmk::AGmkBase {
public:
    // its row of the list's BDAT table: nothing of it is kept (Vector<BdatInfo>::resize allocates a byte an element)
    class BdatInfo {};
    virtual ~GmkSalvageLocator();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x20);
    // the stores Vector<GmkSalvageLocator>::resize makes in each element
    GmkSalvageLocator()
        : pad_48(nullptr), pad_50(nullptr), pad_58(0), m_dropitemEmitter(nullptr), m_gob(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_isAccessed(false),
          pad_d0(nullptr), pad_d8(nullptr), pad_e0(nullptr), pad_e8(-1), pad_ec(0), pad_f0(0), pad_f1(0), pad_f2(0) {}
    void* pad_48;  // the constructor clears it (8-byte store)
    void* pad_50;  // the constructor clears it (8-byte store)
    unsigned char pad_58;  // dispose clears it
    // the destructor runs its destructor (gf::GfDropitemEmitter::dispose) after dispose; the name is not the original's
    gf::GfDropitemEmitter m_dropitemEmitter;
    gf::GF_OBJ_HANDLE* m_gob;  // dispose destroys it unless it is -1 (the name is not the original's)
    bool m_isAccessed;  // onPlayerAccessed sets it, dispose clears it (the name is not the original's)
    unsigned char pad_c9[0x7];
    void* pad_d0;  // dispose sets a byte (0x129) of what it points to
    void* pad_d8;
    void* pad_e0;  // dispose clears it
    int pad_e8;    // dispose sets it to -1
    int pad_ec;    // dispose clears it
    unsigned char pad_f0;  // dispose clears it
    unsigned char pad_f1;  // dispose tests it
    unsigned char pad_f2;  // dispose tests it
    // 0xf3..0x100: tail padding (expand copies up to 0xf3); size from TGmkList::getInst's stride (0x100)
};
}  // namespace gmk

#endif

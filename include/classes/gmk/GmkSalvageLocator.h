#ifndef CLASSES_GMK_GMKSALVAGELOCATOR_H
#define CLASSES_GMK_GMKSALVAGELOCATOR_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
#include "gf/GfDropitemEmitter.h"

namespace gmk { class GmkSalvage; }

namespace gmk {
// table 0x7100B6CAA0
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkSalvageLocator : public ::gmk::AGmkBase {
public:
    // its row of the list's BDAT table: nothing of it is kept (Vector<BdatInfo>::resize allocates a byte an element)
    class BdatInfo {};
    virtual ~GmkSalvageLocator();  // slot 0
    void reqDisposeTboxGobInst(float wait) const;
    void seqWaitPop(float dt);
    void seqPop(float dt);
    void syncDepopTboxes();
    void onEnemyDead(gf::GF_OBJ_HANDLE*);
    void onEnemyHomeToPlayerAccess(gf::GF_OBJ_HANDLE*);
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
        : m_seq(nullptr), pad_58(0), m_dropitemEmitter(nullptr), m_gob(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_isAccessed(false),
          m_salvage(nullptr), m_popWait(0.0f), m_popTimer(0.0f), m_disposeWait(0.0f), pad_e4(0), pad_e8(-1), pad_ec(0), pad_f0(0), pad_f1(0), pad_f2(0) {}
    // its current step (seqWaitPop stores &seqPop; the name is not the original's)
    void (GmkSalvageLocator::*m_seq)(float dt);
    unsigned char pad_58;  // dispose clears it
    // the destructor runs its destructor (gf::GfDropitemEmitter::dispose) after dispose; the name is not the original's
    gf::GfDropitemEmitter m_dropitemEmitter;
    gf::GF_OBJ_HANDLE* m_gob;  // dispose destroys it unless it is -1 (the name is not the original's)
    bool m_isAccessed;  // onPlayerAccessed sets it, dispose clears it (the name is not the original's)
    unsigned char pad_c9[0x7];
    GmkSalvage* m_salvage;  // dispose and syncDepopTboxes set its byte 0x129 (the name is not the original's)
    float m_popWait;   // 0xd8: seqWaitPop waits until m_popTimer reaches it (the name is not the original's)
    float m_popTimer;  // 0xdc
    // 0xe0: reqDisposeTboxGobInst (const) stores its argument here and clears 0xe4 (the names are not the original's)
    mutable float m_disposeWait;
    mutable int pad_e4;
    int pad_e8;    // dispose sets it to -1
    int pad_ec;    // dispose clears it
    unsigned char pad_f0;  // dispose clears it
    unsigned char pad_f1;  // dispose tests it; onEnemyDead sets it
    unsigned char pad_f2;  // dispose tests it; onEnemyHomeToPlayerAccess sets it
    // 0xf3..0x100: tail padding (expand copies up to 0xf3); size from TGmkList::getInst's stride (0x100)
};
}  // namespace gmk

#endif

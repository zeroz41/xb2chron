#ifndef CLASSES_GMK_GMKAREABGM_H
#define CLASSES_GMK_GMKAREABGM_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gmk/IGmkPhantomEventListener.h"
#include "classes/gmk/GmkPhantom.h"
#include "classes/gmk/GmkBgmCondInfo.h"
namespace gmk { class GmkAreaBgmGob; }

namespace gmk {
// a base of gmk::GmkAreaBgm no evidence names yet
class TUnk_B6D7A8 {
public:
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&) = 0;
};
// table 0x7100B6D730; base at 0x48 unknown (TUnk_B6D7A8)
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkAreaBgm : public ::gmk::AGmkBase, public TUnk_B6D7A8 {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x7100601F98 (zero-filled)
    class BdatInfo {
    public:
        // inline: initGmkBdatInfo inlines it (no symbol); the column names are the original's, the field names not
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_bgmCondition = 0;  // the original stores 0 before reading the column
            m_bgmCondition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "bgmCondition", row, 2);
        }
        unsigned short m_bgmCondition = 0;  // its "bgmCondition" column
    };
    // inline: only an inline (linkonce) D2 lets clang defer inlining the four GmkBgmCondInfo destructors into it,
    // as the original's D2 calls them while its D0 inlines them
    virtual ~GmkAreaBgm() { dispose(); }  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) {}  // slot 11
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&);  // slot 12
    void createBgmCondInfos();  // out of line (0x710059CF0C): create's tail call
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(29);
    GmkPhantom m_phantom;  // 0x50: dispose disposes it (the name is not the original's)
    GmkBgmCondInfo m_condInfos[4];  // 0xe0: dispose disposes each (the name is not the original's)
    void* pad_160;  // dispose clears it; 0x168..0x170 is tail padding (Vector<GmkAreaBgm>::expand copies 0xe0..0x168)
};
}  // namespace gmk

#endif

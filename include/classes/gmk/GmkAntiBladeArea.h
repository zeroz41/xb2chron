#ifndef CLASSES_GMK_GMKANTIBLADEAREA_H
#define CLASSES_GMK_GMKANTIBLADEAREA_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gmk/IGmkPhantomEventListener.h"
namespace gmk { class GmkAntiBladeAreaGob; }

namespace gmk {
// a base of gmk::GmkAntiBladeArea no evidence names yet
class TUnk_B6E320 {
public:
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&) = 0;
};
// table 0x7100B6E2A8; base at 0x48 unknown (TUnk_B6E320)
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkAntiBladeArea : public ::gmk::AGmkBase, public TUnk_B6E320 {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x710062A048 (zero-filled)
    class BdatInfo {
    public:
        // its row's id (GfFieldGimmick::getBdatIdOfActiveGmkAntiBladeArea returns it; the name is not the
        // original's)
        unsigned short m_bdatId = 0;  // read from its "BTL_MapRevId" column
        // inline: initGmkBdatInfo inlines it (no symbol); the column names are the original's, the field names not
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_bdatId = 0;  // the original stores 0 before reading the column
            m_bdatId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "BTL_MapRevId", row, 2);
        }
    };
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    virtual ~GmkAntiBladeArea();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugDraw() const;  // slot 7
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&);  // slot 11
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&);  // slot 12
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(56);
    unsigned char pad_50[0xa0];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif

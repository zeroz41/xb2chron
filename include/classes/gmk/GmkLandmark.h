#ifndef CLASSES_GMK_GMKLANDMARK_H
#define CLASSES_GMK_GMKLANDMARK_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/IGmkPhantomEventListener.h"
#include "plugin/Bdat.h"
namespace gmk { class GmkLandmarkGob; }

namespace gmk {
// a base of gmk::GmkLandmark no evidence names yet
class TUnk_B6C7B0 {
public:
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;
    virtual void vf1();
};
// table 0x7100B6C738; base at 0x48 unknown (TUnk_B6C7B0)
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkLandmark : public ::gmk::AGmkBase, public TUnk_B6C7B0 {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x71005F51B8 (whose constructor sets its fields; their defaults are not written yet)
    class BdatInfo {
    public:
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isCondMatched() const;
        // the row's "MSGID": the landmark's name in BDAT 0x1B3's messages (GfFieldManager::getLandmarkNameId hands it out; the name is
        // not the original's)
        unsigned short m_nameId;
        unsigned char m_category;  // the row's "category"
        unsigned char pad_3;
        unsigned short m_cndId;  // the row's "cndID" (a GfGameCond id; 0: none)
        bool m_noTelop;  // the row's "flag" bit "noTelop"
        unsigned char pad_7;
        const char* m_name;  // m_nameId's text in BDAT 0x1B3 (set when m_nameId is nonzero)
    };
    virtual ~GmkLandmark();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) {}  // slot 11
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&);  // slot 12
    // AGmkBase's row as this kind's BdatInfo; the name is not the original's
    const BdatInfo* getBdatInfo() const {
        return static_cast<const BdatInfo*>(m_bdatInfo);
    }
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(21);
    unsigned char pad_50[0xb0];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif

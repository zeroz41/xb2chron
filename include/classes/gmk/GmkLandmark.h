#ifndef CLASSES_GMK_GMKLANDMARK_H
#define CLASSES_GMK_GMKLANDMARK_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantom.h"
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
        BdatInfo() {}  // user-provided: Vector<BdatInfo>::resize stores only the defaults (pads left)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isCondMatched() const;
        // the row's "MSGID": the landmark's name in BDAT 0x1B3's messages (GfFieldManager::getLandmarkNameId hands it out; the name is
        // not the original's)
        unsigned short m_nameId = 0;
        unsigned char m_category = 0;  // the row's "category"
        unsigned short m_cndId = 0;  // the row's "cndID" (a GfGameCond id; 0: none)
        bool m_noTelop = false;  // the row's "flag" bit "noTelop"
        const char* m_name = nullptr;  // m_nameId's text in BDAT 0x1B3 (set when m_nameId is nonzero)
    };
    virtual ~GmkLandmark();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    bool isFound() const;
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) {}  // slot 11
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&);  // slot 12
    // AGmkBase's row as this kind's BdatInfo; the name is not the original's
    const BdatInfo* getBdatInfo() const {
        return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    }
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(21);
    void disposeGmkPhantom();
    unsigned char pad_50[0x10];
    GmkPhantom m_phantom;  // 0x60: the destructor destroys it (the name is not the original's)
    unsigned char pad_f0[0x10];  // fields: size from TGmkList::getInst's stride (0x100)
};
}  // namespace gmk

#endif

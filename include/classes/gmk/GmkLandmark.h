#ifndef CLASSES_GMK_GMKLANDMARK_H
#define CLASSES_GMK_GMKLANDMARK_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/IGmkPhantomEventListener.h"
namespace gmk { class GmkLandmarkGob; }

namespace gmk {
// a base of gmk::GmkLandmark no evidence names yet
class TUnk_B6C7B0 {
public:
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;
    virtual void vf1();
};
// table 0x7100B6C738; base at 0x48 unknown (TUnk_B6C7B0)
class GmkLandmark : public ::gmk::AGmkBase, public TUnk_B6C7B0 {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x71005F51B8 (whose constructor sets its fields; their defaults are not written yet)
    class BdatInfo {
    public:
        bool isCondMatched() const;
        // the landmark's name in BDAT 0x1B3's messages (GfFieldManager::getLandmarkNameId hands it out; the name is
        // not the original's)
        unsigned short m_nameId;
        unsigned char pad_2[0xE];
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

#ifndef CLASSES_GMK_GMKTBOX_H
#define CLASSES_GMK_GMKTBOX_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkTboxGob; }

namespace gmk {
// table 0x7100B6C3B0
class GmkTbox : public ::gmk::AGmkBase {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x71005DFFBC (zero-filled)
    class BdatInfo {
    public:
        bool isPopCondMatchedExceptDist() const;
        unsigned short m_condition;  // the row's "Condition" (a GfGameCond id; 0: none)
        unsigned char pad_2[0xE];
    };
    virtual ~GmkTbox();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    void setTargetable(bool targetable) const;
    int getProgress() const;
    // AGmkBase's row as this kind's BdatInfo; the name is not the original's
    const BdatInfo* getBdatInfo() const {
        return static_cast<const BdatInfo*>(m_bdatInfo);
    }
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(9);
    // its game object (dispose clears its user data, destroys it and stores -1; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob;
    unsigned char pad_50[0x10];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif

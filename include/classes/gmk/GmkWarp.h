#ifndef CLASSES_GMK_GMKWARP_H
#define CLASSES_GMK_GMKWARP_H

#include "classes/gmk/AGmkBase.h"
#include "mm/Vec3NA.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkWarpGobCustom; }

namespace gmk {
// table 0x7100B6CCA8
class GmkWarp : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        unsigned char pad_0[0x18];
    };
    virtual ~GmkWarp();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*) {}  // slot 9
    virtual void debugUpdateMmf();  // slot 10
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    // one end of the warp in AGmkBase::m_data (GfFieldWarp::onFsSucceeded reads two of them; the names are not the
    // original's)
    struct Point {
        mm::Vec3NA m_pos;
        float m_param;  // passed on in MsgPcFieldNotifyWarp (meaning not known)
    };
    const Point* getPoints() const { return reinterpret_cast<const Point*>(m_data); }
    static const gmk::GmkType TYPE = gmk::GmkType(38);
    unsigned char pad_48[0x8];  // fields: size from TGmkList::getInst's stride
    // the object at the first point (inferred): GfFieldWarp::onFsSucceeded sends the player to the second point when
    // the access came from it, to the first from any other (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_firstHandle;
    unsigned char pad_58[0x18];
};
}  // namespace gmk

#endif

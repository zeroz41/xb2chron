#ifndef CLASSES_GMK_GMKNPC_H
#define CLASSES_GMK_GMKNPC_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}
namespace mm { class Vec3; }

namespace gmk {
// a base of gmk::GmkNpc no evidence names yet
class TUnk_B6DB08 {
public:
    virtual ~TUnk_B6DB08();
    virtual bool isPopCondMatched() const = 0;
    virtual void isDepopCondMatched() const = 0;
    virtual void vf4();
    virtual void vf5();
    virtual void getBindedBdatFp() const = 0;
    virtual void getBindedBdatId() const = 0;
    virtual void findPopPosRot(mm::Vec3&, mm::Vec3&) const = 0;
    virtual void bindToGameObj(gf::GF_OBJ_HANDLE*) const = 0;
    virtual void unbindToGameObj(gf::GF_OBJ_HANDLE*) const = 0;
    virtual void validateDisp() const = 0;
    virtual void debugUpdate(float) = 0;
};
// table 0x7100B6DA48; base at 0x48 unknown (TUnk_B6DB08)
class GmkNpc : public ::gmk::AGmkBase, public TUnk_B6DB08 {
public:
    class BdatInfo;
    virtual ~GmkNpc();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual bool isPopCondMatched() const;  // slot 11
    virtual void isDepopCondMatched() const;  // slot 12
    virtual void vf13();  // slot 13
    virtual void vf14();  // slot 14
    virtual void getBindedBdatFp() const;  // slot 15
    virtual void getBindedBdatId() const;  // slot 16
    virtual void findPopPosRot(mm::Vec3&, mm::Vec3&) const;  // slot 17
    virtual void bindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 18
    virtual void unbindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 19
    virtual void validateDisp() const;  // slot 20
    virtual void debugUpdate(float) {}  // slot 21
};
}  // namespace gmk

#endif

#ifndef CLASSES_GMK_GMKNPC_H
#define CLASSES_GMK_GMKNPC_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gmk/AGmkNpc.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkNpcGob; }
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B6DA48; secondary base AGmkNpc at 0x48 (its sub-table 0x7100B6DB08)
class GmkNpc : public ::gmk::AGmkBase, public ::gmk::AGmkNpc {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        // out of line: initGmkBdatInfo calls it (symbol 0x710058E934)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        unsigned char pad_0[0x30];
    };
    virtual ~GmkNpc();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual bool isPopCondMatched() const;  // slot 11
    virtual void isDepopCondMatched() const;  // slot 12
    virtual void vf4();  // slot 13 (AGmkNpc slot 4)
    virtual void vf5();  // slot 14 (AGmkNpc slot 5)
    virtual void getBindedBdatFp() const;  // slot 15
    virtual void getBindedBdatId() const;  // slot 16
    virtual bool findPopPosRot(mm::Vec3&, mm::Vec3&) const;  // slot 17
    virtual void bindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 18
    virtual void unbindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 19
    virtual void validateDisp() const;  // slot 20
    virtual void debugUpdate(float) {}  // slot 21
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(3);
    unsigned char pad_50[0x20];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif

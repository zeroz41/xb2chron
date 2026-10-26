#ifndef CLASSES_GMK_GMKGRAVE_H
#define CLASSES_GMK_GMKGRAVE_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkGraveGob; }

namespace gmk {
// table 0x7100B6CBD8
class GmkGrave : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        unsigned char pad_0[0x2];
        // what gf::GfFieldGrave::create passes the common window (fn_7100359CD8) with message 51; the name is not
        // the original's
        unsigned short m_windowArg;
        unsigned char pad_4[0x10];
    };
    virtual ~GmkGrave();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // pops the grave's enemy (gf::GfFieldGrave::seqWaitToSelect calls it on the common window's first choice)
    bool reqPopEnemy() const;
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*) {}  // slot 9
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(35);
    unsigned char pad_48[0x8];
    // its game object (dispose clears its user data, destroys it and stores -1; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob;
    unsigned char pad_58[0x48];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif

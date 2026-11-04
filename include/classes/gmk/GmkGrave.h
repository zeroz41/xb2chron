#ifndef CLASSES_GMK_GMKGRAVE_H
#define CLASSES_GMK_GMKGRAVE_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkAcc.h"

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
        // out of line: initGmkBdatInfo calls it with the table itself (symbol 0x71005A5230)
        void create(unsigned char* fp, int row, const AGmkBase& gmk);
        unsigned char pad_0[0x2];
        // what gf::GfFieldGrave::create passes the common window (GfMenuManager::openCommonWindowWithNamed) with message 51; the name is not
        // the original's
        unsigned short m_windowArg;
        unsigned char pad_4[0x10];
    };
    // user-provided: Vector<GmkGrave>::resize stores the defaults below only (no zero fill of the element first)
    GmkGrave() {}
    virtual ~GmkGrave();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // pops the grave's enemy (gf::GfFieldGrave::seqWaitToSelect calls it on the common window's first choice)
    bool reqPopEnemy() const;
    // reqPopEnemy's per-kind halves (out of line in the original: _ZNK3gmk8GmkGrave11reqPopEnemyINS_8GmkEnemyEEEbv)
    template <class T> bool reqPopEnemy() const;
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*) {}  // slot 9
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(35);
    unsigned char pad_48 = 0;  // (0x49..0x4f: a hole, not stored or copied)
    // its game object (dispose clears its user data, destroys it and stores -1; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    // 0x58: an access (Vector<GmkGrave>::resize inlines GmkAcc's constructor here; the name is not the original's)
    GmkAcc m_acc;
    unsigned char pad_98 = 0;
    unsigned char pad_99 = 1;  // (0x9a..0x9f: tail padding; the size: TGmkList::getInst's stride)
};
}  // namespace gmk

#endif

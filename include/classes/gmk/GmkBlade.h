#ifndef CLASSES_GMK_GMKBLADE_H
#define CLASSES_GMK_GMKBLADE_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkBladeGob; }

namespace gmk {
// table 0x7100B6E108
class GmkBlade : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        // GfGmkBladeTraverser::onTraverse compares it with its own (the name is not the original's)
        unsigned char m_kind;  // 0x0
        unsigned char pad_1[0x2F];
    };
    virtual ~GmkBlade();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(47);
    unsigned char pad_48[0x8];  // fields: size from TGmkList::getInst's stride
    // GfGmkBladeTraverser::onTraverse compares it with its id, or with 1001 and 1002 (the name is not the original's)
    int m_bladeId;  // 0x50
    unsigned char pad_54[0x4];
};
}  // namespace gmk

#endif

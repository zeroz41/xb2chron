#ifndef CLASSES_GMK_GMKDMGGIMMICK_H
#define CLASSES_GMK_GMKDMGGIMMICK_H

#include "mm/mtl/RTTI.h"
#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
namespace gmk { class GmkDmgGimmickGobCustom; }

namespace gmk {
// a base of gmk::GmkDmgGimmick no evidence names yet
class TUnk_B6CF80 {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;
};
// table 0x7100B6CF10; base at 0x48 unknown (TUnk_B6CF80)
class GmkDmgGimmick : public ::gmk::AGmkBase, public TUnk_B6CF80 {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        // out of line: initGmkBdatInfo calls it (symbol 0x71005AFF0C)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        unsigned char pad_0[0x28];
    };
    virtual ~GmkDmgGimmick();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 11
    static mm::mtl::RTTI m_rtti;
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(48);
    unsigned char pad_50[0x38];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif

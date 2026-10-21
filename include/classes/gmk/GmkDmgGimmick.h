#ifndef CLASSES_GMK_GMKDMGGIMMICK_H
#define CLASSES_GMK_GMKDMGGIMMICK_H

#include "mm/mtl/RTTI.h"
#include "classes/gmk/AGmkBase.h"

namespace gmk {
// a base of gmk::GmkDmgGimmick no evidence names yet
class TUnk_B6CF80 {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;
};
// table 0x7100B6CF10; base at 0x48 unknown (TUnk_B6CF80)
class GmkDmgGimmick : public ::gmk::AGmkBase, public TUnk_B6CF80 {
public:
    class BdatInfo;
    virtual ~GmkDmgGimmick();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 11
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gmk

#endif

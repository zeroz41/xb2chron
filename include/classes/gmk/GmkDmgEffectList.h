#ifndef CLASSES_GMK_GMKDMGEFFECTLIST_H
#define CLASSES_GMK_GMKDMGEFFECTLIST_H

#include "classes/gmk/GmkDmgEffect.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkDmgEffect; }
namespace gmk { class GmkDmgEffectGob; }

namespace gmk {
// table 0x7100B6E948
class GmkDmgEffectList : public ::gmk::TGmkList<gmk::GmkDmgEffect, gmk::GmkDmgEffect::BdatInfo, 1178946884u, 1u, gmk::GmkDmgEffectGob> {
public:
    virtual ~GmkDmgEffectList();  // slot 0
    virtual void getInst(unsigned int) const;  // slot 6
};
}  // namespace gmk

#endif

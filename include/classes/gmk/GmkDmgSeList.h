#ifndef CLASSES_GMK_GMKDMGSELIST_H
#define CLASSES_GMK_GMKDMGSELIST_H

#include "classes/gmk/GmkDmgSe.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkDmgSe; }
namespace gmk { class GmkDmgSeGob; }

namespace gmk {
// table 0x7100B6EA98
class GmkDmgSeList : public ::gmk::TGmkList< ::gmk::GmkDmgSe, ::gmk::GmkDmgSe::BdatInfo, 1163087172u, 2u, ::gmk::GmkDmgSeGob> {
public:
    virtual ~GmkDmgSeList();  // slot 0
    virtual gmk::AGmkBase* getInst(unsigned int) const;  // slot 6
};
}  // namespace gmk

#endif

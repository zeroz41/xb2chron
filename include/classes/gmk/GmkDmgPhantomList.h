#ifndef CLASSES_GMK_GMKDMGPHANTOMLIST_H
#define CLASSES_GMK_GMKDMGPHANTOMLIST_H

#include "classes/gmk/GmkDmgPhantom.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkDmgPhantom; }
namespace gmk { class GmkDmgPhantomGob; }

namespace gmk {
// table 0x7100B6E7F8
class GmkDmgPhantomList : public ::gmk::TGmkList< ::gmk::GmkDmgPhantom, ::gmk::GmkDmgPhantom::BdatInfo, 1213222212u, 2u, ::gmk::GmkDmgPhantomGob> {
public:
    virtual ~GmkDmgPhantomList();  // slot 0
    virtual void getInst(unsigned int) const;  // slot 6
};
}  // namespace gmk

#endif

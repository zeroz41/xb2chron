#ifndef CLASSES_IDCOLI_IDCOLIOBJPHANTOM_H
#define CLASSES_IDCOLI_IDCOLIOBJPHANTOM_H

#include "classes/idcoli/IDColiObjBase.h"

namespace idcoli {
// table none (its derived classes')
// derives from IDColiObjBase: IDColiObjPhantomCheck's constructor stores IDColiObjBase's table
class IDColiObjPhantom : public ::idcoli::IDColiObjBase {
public:
    virtual ~IDColiObjPhantom() {}  // slot 0
    virtual void sizeUpdate();  // slot 3
    virtual void update();  // slot 4
    virtual bool SweepAndPruneUpdate();  // slot 5
    virtual void consistentUpdate();  // slot 6
};
}  // namespace idcoli

#endif

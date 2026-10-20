#ifndef CLASSES_IDCOLI_IDCOLIOBJPHANTOM_H
#define CLASSES_IDCOLI_IDCOLIOBJPHANTOM_H

#include "classes/idcoli/IDColiObj.h"

namespace idcoli {
// table none (its derived classes')
class IDColiObjPhantom : public ::idcoli::IDColiObj {
public:
    virtual ~IDColiObjPhantom();  // slot 0
    virtual void sizeUpdate();  // slot 3
    virtual void update();  // slot 4
    virtual void SweepAndPruneUpdate();  // slot 5
    virtual void consistentUpdate();  // slot 6
};
}  // namespace idcoli

#endif

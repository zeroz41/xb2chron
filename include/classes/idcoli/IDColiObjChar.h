#ifndef CLASSES_IDCOLI_IDCOLIOBJCHAR_H
#define CLASSES_IDCOLI_IDCOLIOBJCHAR_H

#include "classes/idcoli/IDColiObjBase.h"

namespace idcoli {
// table 0x7100B7F210
class IDColiObjChar : public ::idcoli::IDColiObjBase {
public:
    virtual ~IDColiObjChar();  // slot 0
    virtual void release();  // slot 2
    virtual void sizeUpdate();  // slot 3
    virtual void update();  // slot 4
    virtual void SweepAndPruneUpdate();  // slot 5
    virtual void consistentUpdate();  // slot 6
};
}  // namespace idcoli

#endif

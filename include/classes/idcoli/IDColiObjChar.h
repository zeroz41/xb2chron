#ifndef CLASSES_IDCOLI_IDCOLIOBJCHAR_H
#define CLASSES_IDCOLI_IDCOLIOBJCHAR_H

#include "idcoli/IDColiObjData.h"

namespace idcoli {
// table 0x7100B7F210
// an IDColiObjData: IDColiParmsCharacter::createData calls IDColiObjData::createBinary on it unadjusted
class IDColiObjChar : public ::idcoli::IDColiObjData {
public:
    virtual ~IDColiObjChar();  // slot 0
    virtual void release();  // slot 2
    virtual void sizeUpdate();  // slot 3
    virtual void update();  // slot 4
    virtual bool SweepAndPruneUpdate();  // slot 5
    virtual void consistentUpdate();  // slot 6
};
}  // namespace idcoli

#endif

#ifndef CLASSES_IDCOLI_IDCOLIOBJGRAND_H
#define CLASSES_IDCOLI_IDCOLIOBJGRAND_H

#include "classes/idcoli/IDColiObj.h"

namespace idcoli {
// table 0x7100B7F5A0
class IDColiObjGrand : public ::idcoli::IDColiObj {
public:
    virtual ~IDColiObjGrand();  // slot 0
    virtual void update();  // slot 4
};
}  // namespace idcoli

#endif

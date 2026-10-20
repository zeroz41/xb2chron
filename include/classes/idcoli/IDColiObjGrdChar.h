#ifndef CLASSES_IDCOLI_IDCOLIOBJGRDCHAR_H
#define CLASSES_IDCOLI_IDCOLIOBJGRDCHAR_H

#include "classes/idcoli/IDColiObj.h"

namespace idcoli {
// table 0x7100B7F5E8
class IDColiObjGrdChar : public ::idcoli::IDColiObj {
public:
    virtual ~IDColiObjGrdChar();  // slot 0
    virtual void update();  // slot 4
};
}  // namespace idcoli

#endif

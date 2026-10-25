#ifndef CLASSES_IDCOLI_IDCOLIOBJCHARCHECK_H
#define CLASSES_IDCOLI_IDCOLIOBJCHARCHECK_H

#include "classes/idcoli/IDColiObjChar.h"

namespace idcoli { class IDColiTreeTop; }

namespace idcoli {
// table 0x7100B7F138
class IDColiObjCharCheck : public ::idcoli::IDColiObjChar {
public:
    IDColiObjCharCheck(IDColiTreeTop* tree);
    virtual ~IDColiObjCharCheck();  // slot 0
};
}  // namespace idcoli

#endif

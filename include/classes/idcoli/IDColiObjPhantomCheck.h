#ifndef CLASSES_IDCOLI_IDCOLIOBJPHANTOMCHECK_H
#define CLASSES_IDCOLI_IDCOLIOBJPHANTOMCHECK_H

#include "classes/idcoli/IDColiObjPhantom.h"

namespace idcoli { class IDColiTreeTop; }

namespace idcoli {
// table 0x7100B7F258
class IDColiObjPhantomCheck : public ::idcoli::IDColiObjPhantom {
public:
    IDColiObjPhantomCheck(IDColiTreeTop* tree);
    virtual ~IDColiObjPhantomCheck();  // slot 0
};
}  // namespace idcoli

#endif

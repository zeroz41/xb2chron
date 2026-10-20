#ifndef CLASSES_IDCOLI_IDCOLIMANAGER_H
#define CLASSES_IDCOLI_IDCOLIMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace idcoli { class IDColiManager; }

namespace idcoli {
// table 0x7100B7F068
class IDColiManager : public ::mm::mtl::PtrSingleton< ::idcoli::IDColiManager> {
public:
    virtual ~IDColiManager();  // slot 0
};
}  // namespace idcoli

#endif

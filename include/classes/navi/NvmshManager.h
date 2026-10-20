#ifndef CLASSES_NAVI_NVMSHMANAGER_H
#define CLASSES_NAVI_NVMSHMANAGER_H

#include "classes/ml/IWorkEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace navi { class NvmshManager; }

namespace navi {
// table 0x7100B7F630
class NvmshManager : public ::mm::mtl::PtrSingleton< ::navi::NvmshManager>, public ::ml::IWorkEvent {
public:
    virtual ~NvmshManager();  // slot 0
};
}  // namespace navi

#endif

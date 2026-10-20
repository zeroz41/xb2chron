#ifndef CLASSES_FW_PARAMMANAGER_H
#define CLASSES_FW_PARAMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class ParamManager; }

namespace fw {
// table 0x7100B41898
class ParamManager : public ::mm::mtl::PtrSingleton< ::fw::ParamManager> {
public:
    virtual ~ParamManager();  // slot 0
};
}  // namespace fw

#endif

#ifndef CLASSES_FW_EFFECTLODMANAGER_H
#define CLASSES_FW_EFFECTLODMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class EffectLodManager; }

namespace fw {
// table 0x7100B41390
class EffectLodManager : public ::mm::mtl::PtrSingleton< ::fw::EffectLodManager> {
public:
    virtual ~EffectLodManager();  // slot 0
};
}  // namespace fw

#endif

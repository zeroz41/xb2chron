#ifndef CLASSES_FW_TRANSFORMMANAGER_H
#define CLASSES_FW_TRANSFORMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class TransformManager; }

namespace fw {
// table 0x7100B417A0
class TransformManager : public ::mm::mtl::PtrSingleton< ::fw::TransformManager> {
public:
    virtual ~TransformManager();  // slot 0
    void update(unsigned int layerMask);  // Framework::update runs it per layer
};
}  // namespace fw

#endif

#ifndef CLASSES_FW_FRAMEWORK_H
#define CLASSES_FW_FRAMEWORK_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mtl/AllocHandle.h"

namespace fw { class Framework; }
namespace ml { class Scn; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B41668
class Framework : public ::mm::mtl::PtrSingleton< ::fw::Framework> {
public:
    virtual ~Framework();  // slot 0
    static mm::mtl::IAllocator* getAllocator();
    static mtl::ALLOC_HANDLE getMemHandle();  // the memory resources are made in (ResourceManager::getMemSYS)
    static unsigned int getFrameCount();
    unsigned char pad_8[0x50];
    ml::Scn* m_scn;  // what LayerSetManager gives layer::LayerManager; the name is not the original's
};
}  // namespace fw

#endif

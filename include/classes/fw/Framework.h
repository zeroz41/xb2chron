#ifndef CLASSES_FW_FRAMEWORK_H
#define CLASSES_FW_FRAMEWORK_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class Framework; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B41668
class Framework : public ::mm::mtl::PtrSingleton< ::fw::Framework> {
public:
    virtual ~Framework();  // slot 0
    static mm::mtl::IAllocator* getAllocator();
};
}  // namespace fw

#endif

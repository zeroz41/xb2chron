#ifndef CLASSES_ML_DEVFILEARCHIVER_H
#define CLASSES_ML_DEVFILEARCHIVER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class DevFileArchiver; }

namespace ml {
// table 0x7100B76E78
class DevFileArchiver : public ::mm::mtl::PtrSingleton< ::ml::DevFileArchiver> {
public:
    virtual ~DevFileArchiver();  // slot 0
};
}  // namespace ml

#endif

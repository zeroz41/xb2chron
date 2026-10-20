#ifndef CLASSES_ML_DEVSETTING_H
#define CLASSES_ML_DEVSETTING_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class DevSetting; }

namespace ml {
// table 0x7100B761B0
class DevSetting : public ::mm::mtl::PtrSingleton< ::ml::DevSetting> {
public:
    virtual ~DevSetting();  // slot 0
};
}  // namespace ml

#endif

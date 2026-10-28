#ifndef CLASSES_ML_DRPIXLMEMMAN_H
#define CLASSES_ML_DRPIXLMEMMAN_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class DrPixlMemMan; }

namespace ml {
// table 0x7100B7CDE0
class DrPixlMemMan : public ::mm::mtl::PtrSingleton< ::ml::DrPixlMemMan> {
public:
    DrPixlMemMan();
    virtual ~DrPixlMemMan();  // slot 0
    void setupMemBuff();
};
}  // namespace ml

#endif

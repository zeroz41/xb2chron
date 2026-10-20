#ifndef CLASSES_ML_DRCALCTEXSTREAMMAN_H
#define CLASSES_ML_DRCALCTEXSTREAMMAN_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class DrCalcTexStreamMan; }

namespace ml {
// table 0x7100B7EDA8
class DrCalcTexStreamMan : public ::mm::mtl::PtrSingleton< ::ml::DrCalcTexStreamMan> {
public:
    virtual ~DrCalcTexStreamMan();  // slot 0
};
}  // namespace ml

#endif

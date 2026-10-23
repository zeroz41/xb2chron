#ifndef ML_DRCALCGPUCOST_H
#define ML_DRCALCGPUCOST_H

namespace ml {

// only the destructor is declared so far (its owners' destructors call it; its body is empty). Fields and other
// members are not declared yet.
class DrCalcGpuCost {
public:
    ~DrCalcGpuCost();
};

}  // namespace ml

#endif

#ifndef CLASSES_ML_FIXED_SIZE_ALLOC_INSIDE_H
#define CLASSES_ML_FIXED_SIZE_ALLOC_INSIDE_H

namespace ml {
// a template: 10 instances in the module
template <typename T0, int T1>
class fixed_size_alloc_inside {
public:
    virtual ~fixed_size_alloc_inside();  // slot 0
};
}  // namespace ml

#endif

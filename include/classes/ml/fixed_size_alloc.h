#ifndef CLASSES_ML_FIXED_SIZE_ALLOC_H
#define CLASSES_ML_FIXED_SIZE_ALLOC_H

namespace ml {
// a template: 2 instances in the module
template <typename T0>
class fixed_size_alloc {
public:
    virtual ~fixed_size_alloc();  // slot 0
};
}  // namespace ml

#endif

#ifndef CLASSES_ML_THREADVAL_H
#define CLASSES_ML_THREADVAL_H

namespace ml {
// a template: 6 instances in the module
template <typename T0>
class threadval {
public:
    virtual ~threadval();  // slot 0
    virtual void tvSwap();  // slot 2
    virtual void getCpuBank() const;  // slot 3
    virtual void setCpuBank(unsigned char);  // slot 4
};
}  // namespace ml

#endif

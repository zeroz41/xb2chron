#ifndef CLASSES_SSD_BEHAVIORINSTANCE_H
#define CLASSES_SSD_BEHAVIORINSTANCE_H

namespace ssd {
// a template: 1 instances in the module
template <typename T0>
class BehaviorInstance {
public:
    virtual ~BehaviorInstance();  // slot 0
    virtual void ExecBehaviorInstance(float);  // slot 2
};
}  // namespace ssd

#endif

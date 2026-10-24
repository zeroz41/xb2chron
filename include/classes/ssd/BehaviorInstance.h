#ifndef CLASSES_SSD_BEHAVIORINSTANCE_H
#define CLASSES_SSD_BEHAVIORINSTANCE_H

#include "classes/ssd/List.h"

namespace ssd {
// a value moved from its start to a target over a time, linked in a List<BehaviorControl> (SystemCore's at
// 0x978); BehaviorInstance<T> calls a member of T with it. No table of its own is left in the module (its
// constructor is inline). The field names are not the original's.
class BehaviorControl : public List<BehaviorControl>::Node {
public:
    virtual void ExecBehaviorInstance(float frameTime) = 0;  // slot 2

    float value_;
    int state_;  // SystemCore::SetMasterVolume / SetMasterPitch reset it to 0
    float start_;
    float target_;
    float elapsed_;
    float time_;
};
// a template: 1 instances in the module (SystemCore's master volume and pitch). Calls object's member
// function with the frame time; the member names are not the original's.
template <typename T0>
class BehaviorInstance : public BehaviorControl {
public:
    typedef void (T0::*Function)(float frameTime);

    virtual void ExecBehaviorInstance(float frameTime) {  // slot 2
        (object_->*function_)(frameTime);
    }

    // starts a move from the current value to target over time, calling function on the way
    void Start(T0* object, Function function, float target, float time) {
        object_ = object;
        function_ = function;
        state_ = 0;
        start_ = value_;
        target_ = target;
        elapsed_ = 0.0f;
        time_ = time;
    }

    T0* object_;
    Function function_;
};
}  // namespace ssd

#endif

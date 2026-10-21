#ifndef CLASSES_ML_IDEVINPUTTOUCH_H
#define CLASSES_ML_IDEVINPUTTOUCH_H

namespace ml {
// table 0x7100B77568
class IDevInputTouch {
public:
    virtual ~IDevInputTouch() {}  // slot 0
    virtual void vf2() = 0;  // slot 2
    virtual void vf3() = 0;  // slot 3
    virtual void vf4() = 0;  // slot 4
};
}  // namespace ml

#endif

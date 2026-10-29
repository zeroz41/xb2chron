#ifndef CLASSES_ML_IDEVINPUTTOUCH_H
#define CLASSES_ML_IDEVINPUTTOUCH_H

namespace ml {
// table 0x7100B77568; ml::DevTouch's base at 0x1A8 (its secondary table's slots are DevTouch's itDown/itUp/itMove
// thunks, and 1.0.0's DevTouch constructor stores this table there)
class IDevInputTouch {
public:
    virtual ~IDevInputTouch() {}  // slot 0
    virtual void itDown(unsigned int, float, float) = 0;  // slot 2
    virtual void itUp(unsigned int, float, float) = 0;  // slot 3
    virtual void itMove(unsigned int, float, float) = 0;  // slot 4
};
}  // namespace ml

#endif

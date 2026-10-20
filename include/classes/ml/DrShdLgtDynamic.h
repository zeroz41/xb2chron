#ifndef CLASSES_ML_DRSHDLGTDYNAMIC_H
#define CLASSES_ML_DRSHDLGTDYNAMIC_H

namespace ml {
// table none (its derived classes')
class DrShdLgtDynamic {
public:
    virtual ~DrShdLgtDynamic();  // slot 0
    virtual void stockBegin() = 0;  // slot 2
    virtual void stockEnd() = 0;  // slot 3
    virtual void update() = 0;  // slot 4
    virtual void setupCate(int);  // slot 5
};
}  // namespace ml

#endif

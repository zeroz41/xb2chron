#ifndef CLASSES_ML_DRMAN_H
#define CLASSES_ML_DRMAN_H

#include "classes/ml/IWorkBackground.h"

namespace ml {
// table 0x7100B7ABB0
class DrMan : public ::ml::IWorkBackground {
public:
    virtual ~DrMan();  // slot 0
    virtual void bkgHomeMenu(bool);  // slot 2
};
}  // namespace ml

#endif

#ifndef CLASSES_ML_DRRESMDOSORTMPF_H
#define CLASSES_ML_DRRESMDOSORTMPF_H

#include "classes/ml/DrMdoZSortObj.h"

namespace ml {
// table 0x7100B7E200
class DrResMdoSortMpf : public ::ml::DrMdoZSortObj {
public:
    virtual ~DrResMdoSortMpf();  // slot 0
    virtual void ZPrepassRender();  // slot 3
    virtual void render();  // slot 6
};
}  // namespace ml

#endif

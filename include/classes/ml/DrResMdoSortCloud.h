#ifndef CLASSES_ML_DRRESMDOSORTCLOUD_H
#define CLASSES_ML_DRRESMDOSORTCLOUD_H

#include "classes/ml/DrMdoZSortObj.h"

namespace ml {
// table 0x7100B7E3C0
class DrResMdoSortCloud : public ::ml::DrMdoZSortObj {
public:
    DrResMdoSortCloud(void* owner);
    virtual ~DrResMdoSortCloud();  // slot 0
    virtual void alphaRender();  // slot 9
};
}  // namespace ml

#endif

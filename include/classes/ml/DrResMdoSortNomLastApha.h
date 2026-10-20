#ifndef CLASSES_ML_DRRESMDOSORTNOMLASTAPHA_H
#define CLASSES_ML_DRRESMDOSORTNOMLASTAPHA_H

#include "classes/ml/DrMdoZSortObj.h"

namespace ml {
// table 0x7100B7E040
class DrResMdoSortNomLastApha : public ::ml::DrMdoZSortObj {
public:
    virtual ~DrResMdoSortNomLastApha();  // slot 0
    virtual void alphaRender();  // slot 9
};
}  // namespace ml

#endif

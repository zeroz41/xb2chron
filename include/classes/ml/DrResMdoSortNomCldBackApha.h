#ifndef CLASSES_ML_DRRESMDOSORTNOMCLDBACKAPHA_H
#define CLASSES_ML_DRRESMDOSORTNOMCLDBACKAPHA_H

#include "classes/ml/DrMdoZSortObj.h"
#include "classes/ml/DrMdoCtlNom.h"

namespace ml {
// table 0x7100B7E120
class DrResMdoSortNomCldBackApha : public ::ml::DrMdoZSortObj {
public:
    DrResMdoSortNomCldBackApha(DrMdoCtlNom* owner);
    virtual ~DrResMdoSortNomCldBackApha() {}  // slot 0
    virtual void alphaRender();  // slot 9
};
}  // namespace ml

#endif

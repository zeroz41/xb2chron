#ifndef CLASSES_ML_DRRESMDOSORTSEAMENVMAP_H
#define CLASSES_ML_DRRESMDOSORTSEAMENVMAP_H

#include "classes/ml/DrMdoZSortObj.h"
#include "classes/ml/DrMdoCtlSeamAll.h"

namespace ml {
// table 0x7100B7E350
class DrResMdoSortSeamEnvMap : public ::ml::DrMdoZSortObj {
public:
    DrResMdoSortSeamEnvMap(void* owner);
    virtual ~DrResMdoSortSeamEnvMap();  // slot 0
    virtual void render();  // slot 6
    virtual void GBuffRender();  // slot 7
    virtual void lightPrePassRender();  // slot 8
    virtual void alphaRender();  // slot 9
    virtual void spAlphaRender();  // slot 10
    virtual void refractionRender();  // slot 11
};
}  // namespace ml

#endif

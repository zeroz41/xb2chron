#ifndef CLASSES_ML_DRRESMDOSORTPOS_H
#define CLASSES_ML_DRRESMDOSORTPOS_H

#include "classes/ml/DrMdoZSortObj.h"
#include "classes/ml/DrMdoCtlPos.h"

namespace ml {
// table 0x7100B7E190
class DrResMdoSortPos : public ::ml::DrMdoZSortObj {
public:
    DrResMdoSortPos(DrMdoCtlPos* owner);
    virtual ~DrResMdoSortPos();  // slot 0
    virtual void ZPrepassRender();  // slot 3
    virtual void ThicknessRenderFirst();  // slot 4
    virtual void ThicknessRenderSecond();  // slot 5
    virtual void render();  // slot 6
    virtual void GBuffRender();  // slot 7
    virtual void lightPrePassRender();  // slot 8
    virtual void alphaRender();  // slot 9
    virtual void spAlphaRender();  // slot 10
    virtual void refractionRender();  // slot 11
};
}  // namespace ml

#endif

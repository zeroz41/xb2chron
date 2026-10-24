#ifndef CLASSES_ML_DRMDOCTL_H
#define CLASSES_ML_DRMDOCTL_H

#include "classes/ml/DrMdoMat.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ml {
// table 0x7100B7B680
class DrMdoCtl : public ::ml::DrMdoMat {
public:
    virtual ~DrMdoCtl() {}  // slot 0
    void setMatrix(const mm::Mat44& matrix);
    void setOffsetPos(const mm::Vec3& pos);
};
}  // namespace ml

#endif

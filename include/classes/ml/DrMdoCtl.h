#ifndef CLASSES_ML_DRMDOCTL_H
#define CLASSES_ML_DRMDOCTL_H

#include "classes/ml/DrMdoNode.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ml {
// table 0x7100B7B680
class DrMdoCtl : public ::ml::DrMdoNode {
public:
    // 1.0.0 has DrMdoCtl(int) and DrMdoNode(int) (both 0x104 bytes); 3.0.1's inlines DrMdoNode's
    explicit DrMdoCtl(int viewNum);
    virtual ~DrMdoCtl() {}  // slot 0
    void setMatrix(const mm::Mat44& matrix);
    void setOffsetPos(const mm::Vec3& pos);
    void createWeightVtx(int, unsigned int, unsigned int, bool);
};
}  // namespace ml

#endif

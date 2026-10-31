#ifndef CLASSES_ML_DRMDONODE_H
#define CLASSES_ML_DRMDONODE_H

#include "ml/DrMdoSetup.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ml {
// table none in 3.0.1 (1.0.0: _ZTVN2ml9DrMdoNodeE; its DrMdoNode(int) stores DrMdoMat's table, then its own, then
// 0x188 and 0x180). DrMdoCtl derives from it; 3.0.1 keeps its node getters (getNodeName, getNodeIdx, getNodeMatrix...).
// It adds no fields: 0xE8..0x18C belong to DrMdoSetup, whose uniformBlock_*/unimate_* setters read them.
class DrMdoNode : public ::ml::DrMdoSetup {
public:
    // inline in DrMdoCtl's constructor
    explicit DrMdoNode(int viewNum) : DrMdoSetup(viewNum) {}
    virtual ~DrMdoNode() {}  // slot 0

    const char* getNodeName(int index) const;
    int getNodeIdx(const char* name) const;
    void setNodeMatrix(int index, const mm::Mat44& mat);
    const mm::Mat44& getNodeMatrix(int index) const;
    mm::Mat44* getNodeMatrixPtr(int index);
    void calcMdlNodeCheck();
    void updateMdlPos();
    void calcOfsMat();

};
}  // namespace ml

#endif

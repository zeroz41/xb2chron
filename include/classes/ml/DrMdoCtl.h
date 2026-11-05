#ifndef CLASSES_ML_DRMDOCTL_H
#define CLASSES_ML_DRMDOCTL_H

#include "classes/ml/DrMdoNode.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace grlib { class CGLibVtxInstans; }

namespace ml {
struct MdsMdlInfoHeader;
struct MdsMdlTopHeader;

// table 0x7100B7B680
class DrMdoCtl : public ::ml::DrMdoNode {
public:
    // 1.0.0 has DrMdoCtl(int) and DrMdoNode(int) (both 0x104 bytes); 3.0.1's inlines DrMdoNode's
    explicit DrMdoCtl(int viewNum);
    virtual ~DrMdoCtl() {}  // slot 0
    void setMatrix(const mm::Mat44& matrix);
    void setOffsetPos(const mm::Vec3& pos);
    void createWeightVtx(int, unsigned int, unsigned int, bool);
    void partsDefRender(const MdsMdlInfoHeader*, int, int, bool);
    // mot != 0: the node (motion) shader variants, drawn without the triangle block
    void partsShadowRender(const MdsMdlInfoHeader* info, int triIdx, int mot, int shdOfs);
    void partsShadowDirRender(const MdsMdlInfoHeader* info, int triIdx, int mot);
    void partsShadowBaseRender(const MdsMdlTopHeader* top);
    void partsShadowNukiBaseRender(const MdsMdlTopHeader* top);
    void partsPosShadowRender(const MdsMdlTopHeader* top);
    void partsPosNukiShadowRender(const MdsMdlTopHeader* top);
    // count/first go to grlib::CGLibCtlVertex::setInstanceVertex, instances to DrResMdoVertex::renderIns (the
    // parameter names are not the original's)
    void partsPosNoamShadowRender(const MdsMdlTopHeader* top, grlib::CGLibVtxInstans* inst, unsigned int count,
                                  unsigned int first, unsigned int instances);
};
}  // namespace ml

#endif

#ifndef ML_DRMDOANIM_H
#define ML_DRMDOANIM_H

#include "classes/ml/DrMdoNode.h"
#include "mm/Vec3.h"
namespace mm { class Mat44; }
namespace ml { class DrResMdoMat; }
namespace ml { class DrResEtcPamObj; }
namespace ml { struct MdsFixAnmCate; }
namespace ml { struct MdsFixAnmInf; }

namespace ml {
// table none in 3.0.1 (1.0.0: _ZTVN2ml9DrMdoAnimE). It derives from DrMdoNode and DrMdoCtl from it: 1.0.0's
// DrMdoAnim(int) (0x710082AF38) zeroes DrMdoNode's 0x188/0x180 before storing its own table last, the same shape as
// DrMdoCtl(int), while DrMdoNode(int) stores its table before those two fields.
class DrMdoAnim : public ::ml::DrMdoNode {
public:
    // inline in DrMdoCtl's constructor
    explicit DrMdoAnim(int viewNum) : DrMdoNode(viewNum) {}
    virtual ~DrMdoAnim() {}  // slot 0

    // Runs a material's fixed animation: advances each value's frame in MdoWrkMatRes::m_pFixAnmFrame by rate (or
    // takes an etc-param), then calls its s_pCallAnim callback on mat and work.
    void calcAnim(const MdsFixAnmCate* cate, DrResMdoMat* mat, DrResEtcPamObj* pamObj, float* work, float rate);
    float getHermiteAttr(const MdsFixAnmInf* inf, float frame);
    void updateAnimEnd(float rate, const unsigned int* dispBits, DrResEtcPamObj* pamObj);
    void updateAnimFast(float rate, DrResEtcPamObj* pamObj);
    void calcPlaneMatrix(mm::Mat44* mtx, const float* param);

    static void animcall_UV_Scr_U(DrResMdoMat*, float*, float);
    static void animcall_UV_Scr_V(DrResMdoMat*, float*, float);
    static void animcall_UV_Trans_U(DrResMdoMat*, float*, float);
    static void animcall_UV_Trans_V(DrResMdoMat*, float*, float);
    static void animcall_UV_Rot(DrResMdoMat*, float*, float);
    static void animcall_WorkFloat1(DrResMdoMat*, float*, float);
    static void animcall_MatAlpha(DrResMdoMat*, float*, float);
    static void animcall_MatColorR(DrResMdoMat*, float*, float);
    static void animcall_MatColorG(DrResMdoMat*, float*, float);
    static void animcall_MatColorB(DrResMdoMat*, float*, float);

    static void anmNodeParm_TranX(mm::Vec3*, float);
    static void anmNodeParm_TranY(mm::Vec3*, float);
    static void anmNodeParm_TranZ(mm::Vec3*, float);
    static void anmNodeParm_RotX(mm::Vec3*, float);
    static void anmNodeParm_RotY(mm::Vec3*, float);
    static void anmNodeParm_RotZ(mm::Vec3*, float);
    static void anmNodeParm_SclX(mm::Vec3*, float);
    static void anmNodeParm_SclY(mm::Vec3*, float);
    static void anmNodeParm_SclZ(mm::Vec3*, float);

    static void (*s_pCallAnim[10])(DrResMdoMat*, float*, float);
    static void (*s_pCallAnmNode[9])(mm::Vec3*, float);
};
}  // namespace ml

#endif

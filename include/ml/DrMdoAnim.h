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
// One animated node value (the type name is the symbols'; the field names are not the original's).
struct MdsMdlNodeAnmInfo {
    // one hermite key, 0x10 bytes (the type and field names are not the original's; MdsFixAnmKey's flags are at 0xE)
    struct Key {
        float m_outTangent;      // 0x0: weighs t^3 - 2t^2 + t towards the next key
        float m_inTangent;       // 0x4: weighs t^3 - t^2 from the previous key
        float m_value;           // 0x8
        unsigned short m_frame;  // 0xC
        unsigned char pad_E;
        unsigned char m_flags;   // 0xF: bit 0 holds m_value up to the next key (no interpolation)
    };
    unsigned char pad_0[0x4];
    int m_startFrame;        // 0x4
    int m_endFrame;          // 0x8
    unsigned int m_keyOfs;   // 0xC: from MdoWrkMatRes::m_pEtcRef->m_pData
    int m_keyNum;            // 0x10
};

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
    // a node value at frame: the first key's value before m_startFrame, the last key's from m_endFrame on
    float getNodeAnmHermiteAttr(const MdsMdlNodeAnmInfo* info, float frame);

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

#ifndef CLASSES_ML_DRMDONODE_H
#define CLASSES_ML_DRMDONODE_H

#include "classes/ml/DrMdoMat.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace grlib { class CGLibEtcUniformBlock; }

namespace ml {
// table none in 3.0.1 (1.0.0: _ZTVN2ml9DrMdoNodeE; its DrMdoNode(int) stores DrMdoMat's table, then its own, then
// 0x188 and 0x180). DrMdoCtl derives from it; 3.0.1 keeps its node getters (getNodeName, getNodeIdx, getNodeMatrix...).
class DrMdoNode : public ::ml::DrMdoMat {
public:
    // inline in DrMdoCtl's constructor
    explicit DrMdoNode(int viewNum)
        : DrMdoMat(viewNum), m_scale(1.0f), pad_EC(0), m_gpuRender(false), m_renderPass(0), m_stateFlags(0),
          m_ctlFlags(0), m_ctlFlags2(0), m_aabbMax(0.5f, 0.5f, 0.5f), m_aabbMin(-0.5f, -0.5f, -0.5f),
          m_center(0.0f, 0.0f, 0.0f), pad_140(1.0f, 1.0f, 1.0f), pad_150(0.0f, 0.0f, 0.0f), m_length(0.0f), pad_164(0),
          pad_168(0), pad_16A(0), pad_16B(0), m_nodeMax(0), pad_182(0), pad_184(0), pad_188(0) {}
    virtual ~DrMdoNode() {}  // slot 0

    const char* getNodeName(int index) const;
    int getNodeIdx(const char* name) const;
    void setNodeMatrix(int index, const mm::Mat44& mat);
    const mm::Mat44& getNodeMatrix(int index) const;
    mm::Mat44* getNodeMatrixPtr(int index);
    void calcMdlNodeCheck();
    void updateMdlPos();
    void calcOfsMat();

    // the names are not the original's
    float m_scale;  // 0xE8: DrMdlObj::getInitialVertexAABBMax/Min scale by it on request (the name is not the original's)
    unsigned int pad_EC;
    bool m_gpuRender;  // 0xF0, isGpuRender
    unsigned char pad_F1[0x1];
    // 0xF2: the technique index partsDefRender looks up in the material's technique list; every call*Render pass
    // sets it (7 gbuffer, 4 light pre-pass, 8 refraction, 1 alpha, 0 opaque) (the name is not the original's)
    short m_renderTech;
    // 0xF4: the pass the call*Render functions start (0 opaque, 1 gbuffer, 2 refraction, 3 light pre-pass,
    // 4 alpha, 5 sp-alpha: the bit of m_stateFlags they test) (the name is not the original's)
    short m_renderPass;
    unsigned char pad_F6[0x2];
    unsigned int m_stateFlags;  // 0xF8: DrMdoGrpObj's render passes skip an object without bit 7
    unsigned int m_ctlFlags;  // 0xFC: setAlwaysTexStm, setGpuClip, setOcclusionQuery... each own a bit
    unsigned int m_ctlFlags2;  // 0x100: setDblBuffAlpha's bit
    unsigned char pad_104[0xC];
    mm::Vec3 m_aabbMax;  // 0x110, (0.5, 0.5, 0.5) from the constructor
    mm::Vec3 m_aabbMin;  // 0x120, (-0.5, -0.5, -0.5) from the constructor
    mm::Vec3 m_center;  // 0x130
    mm::Vec3 pad_140;  // 0x140, (1, 1, 1) from the constructor
    mm::Vec3 pad_150;  // 0x150, zeroed by the constructor
    float m_length;  // 0x160
    unsigned int pad_164;
    short pad_168;
    unsigned char pad_16A;
    unsigned char pad_16B;
    unsigned char pad_16C[0x4];
    // 0x170, the DrMdoShdSetShadow *Inst setters bind it while m_bindFlags[0] bit 1 is set (the name is not the
    // original's)
    grlib::CGLibEtcUniformBlock* m_pEtcBlock;
    // 0x178: partsDefRender's bind flags (bit 0: shader changed, bit 4: m_curBindIdx changed); every pass starts
    // with 0x10, 0 (the name is not the original's)
    unsigned char m_bindFlags[2];
    // 0x17A: the triangle uniform block index the shadow and pre-pass shader setters last bound (the name is not
    // the original's)
    short m_curTriBlockIdx;
    // 0x17C/0x17E: the shader and bind index partsDefRender last set; -1 at the start of every pass (the names are
    // not the original's)
    short m_curShaderIdx;
    short m_curBindIdx;
    short m_nodeMax;  // 0x180, getNodeIdx/setNodeMatrix bound by it (the name is not the original's)
    short pad_182;
    unsigned int pad_184;
    unsigned int pad_188;  // 1.0.0's DrMdoNode(int) zeroes it after storing its table
};
}  // namespace ml

#endif

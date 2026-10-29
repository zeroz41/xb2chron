#ifndef CLASSES_ML_DRMDLOBJ_H
#define CLASSES_ML_DRMDLOBJ_H

#include "classes/ml/DrMdoCtl.h"
#include "mm/Vec3.h"
#include "mm/Mat44.h"
#include "mm/Col3.h"

namespace grlib { class CGLibEtcUniformBlock; }
namespace ml { class DrMdoSmlShadowMan; }
namespace ml { class DrResEtcParams; }
namespace ml { struct MdoRimBloomWrk; }

namespace ml {
// table 0x7100B7ABE0
class DrMdlObj : public ::ml::DrMdoCtl {
public:
    explicit DrMdlObj(int viewNum);
    virtual ~DrMdlObj() {}  // slot 0
    virtual void chageShadowObject(ml::DrMdoSmlShadowMan*);  // slot 14
    void setMatrix(const mm::Mat44& matrix);
    void setOffsetPos(const mm::Vec3& pos);
    int getNodeMax() const;
    void setAceVal(int index, float value);
    void setAlpha(float alpha);
    float getAlpha() const;
    void setWriteStencil(bool enable);
    void getInitialVertexAABBMax(mm::Vec3& out, bool scaled) const;
    void getInitialVertexAABBMin(mm::Vec3& out, bool scaled) const;
    void setAceColor(int index, const mm::Col3& color);
    void setAlwaysTexStm(bool enable);
    void setDblBuffAlpha(bool enable);
    void setAlwaysMiddleTexStm(bool enable);
    void setGpuClip(bool enable);
    void setOcclusionQuery(bool enable);
    bool isGpuRender() const;
    void setSpAlphaMode(bool enable);
    void setCamCheckMode(bool enable);
    bool isCamCheckResl() const;
    bool isMdlTexStm() const;
    bool isMemTexStm() const;
    const mm::Vec3& getAABBMax() const;
    const mm::Vec3& getAABBMin() const;
    // ScnObjModelDrSys reads these fields directly (inline); the names are not the original's
    short getGroups() const { return m_groups; }
    void setGroups(int groups) { m_groups = groups; }
    const mm::Vec3& getCenter() const { return m_center; }
    float getLength() const { return m_length; }

    // the model's etc-parameter table (ScnObjAccEtcParams reads it; field names are not the original's)
    struct EtcParamsName {
        unsigned int m_nameOfs;  // from m_strBase
        unsigned char pad_4[0xC];
    };
    struct EtcParamsTable {
        const char* m_strBase;
        const EtcParamsName* m_names;
        DrResEtcParams* m_params;
        unsigned int m_num;
        unsigned int m_flags;  // bit 0: rim bloom (ScnObjAccEtcParams::setRimBloom)
    };

    int getNodeIdx(const char* name) const;
    const char* getNodeName(int index) const;
    void setResBoneMat(int index, const mm::Mat44& mat);
    mm::Mat44 getResBoneMat(int index) const;
    mm::Mat44* getResBoneMatPtr(int index);
    MdoRimBloomWrk* getRimBloomWrk(unsigned int bank);

    // the names are not the original's
    float m_scale;  // 0xE8: getInitialVertexAABBMax/Min scale by it on request (the name is not the original's)
    unsigned char pad_EC[0x4];
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
    mm::Vec3 m_aabbMax;  // 0x110
    mm::Vec3 m_aabbMin;  // 0x120
    mm::Vec3 m_center;  // 0x130
    unsigned char pad_140[0x20];
    float m_length;  // 0x160
    unsigned char pad_164[0xC];
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
    short m_nodeMax;  // 0x180, getNodeMax (the name is not the original's)
};
}  // namespace ml

#endif

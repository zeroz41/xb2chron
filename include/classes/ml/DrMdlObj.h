#ifndef CLASSES_ML_DRMDLOBJ_H
#define CLASSES_ML_DRMDLOBJ_H

#include "classes/ml/DrMdoCtl.h"
#include "mm/Vec3.h"
#include "mm/Mat44.h"

namespace ml { class DrMdoSmlShadowMan; }
namespace ml { class DrResEtcParams; }
namespace ml { struct MdoRimBloomWrk; }

namespace ml {
// table 0x7100B7ABE0
class DrMdlObj : public ::ml::DrMdoCtl {
public:
    virtual ~DrMdlObj();  // slot 0
    virtual void chageShadowObject(ml::DrMdoSmlShadowMan*);  // slot 14
    void setAlpha(float alpha);
    float getAlpha() const;
    void setWriteStencil(bool enable);
    void setAlwaysTexStm(bool enable);
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

    bool isGpuRender() const;
    bool isCamCheckResl() const;
    void setAlwaysMiddleTexStm(bool on);
    void setGpuClip(bool on);
    void setDblBuffAlpha(bool on);
    void setSpAlphaMode(bool on);
    void setCamCheckMode(bool on);
    int getNodeMax() const;
    int getNodeIdx(const char* name) const;
    const char* getNodeName(int index) const;
    void setResBoneMat(int index, const mm::Mat44& mat);
    mm::Mat44 getResBoneMat(int index) const;
    mm::Mat44* getResBoneMatPtr(int index);
    MdoRimBloomWrk* getRimBloomWrk(unsigned int bank);

    // the names are not the original's
    unsigned char pad_DC[0x54];
    mm::Vec3 m_center;  // 0x130
    unsigned char pad_140[0x20];
    float m_length;  // 0x160
};
}  // namespace ml

#endif

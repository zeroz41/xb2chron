#ifndef CLASSES_ML_DRMDLOBJ_H
#define CLASSES_ML_DRMDLOBJ_H

#include "classes/ml/DrMdoCtl.h"
#include "mm/Vec3.h"
#include "mm/Mat44.h"
#include "mm/Col3.h"

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


    int getNodeIdx(const char* name) const;
    const char* getNodeName(int index) const;
    void setResBoneMat(int index, const mm::Mat44& mat);
    const mm::Mat44& getResBoneMat(int index) const;
    mm::Mat44* getResBoneMatPtr(int index);
    MdoRimBloomWrk* getRimBloomWrk(unsigned int bank);
};
}  // namespace ml

#endif

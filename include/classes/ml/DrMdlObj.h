#ifndef CLASSES_ML_DRMDLOBJ_H
#define CLASSES_ML_DRMDLOBJ_H

#include "classes/ml/DrMdoCtl.h"
#include "mm/Vec3.h"

namespace ml { class DrMdoSmlShadowMan; }

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

    // DrMdoCtl's fields are not declared yet: pad_8 covers them up to 0x18
    unsigned char pad_8[0x10];
    short m_groups;  // 0x18
    unsigned char pad_1A[0x116];
    mm::Vec3 m_center;  // 0x130
    unsigned char pad_140[0x20];
    float m_length;  // 0x160
};
}  // namespace ml

#endif

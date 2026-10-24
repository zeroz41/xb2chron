#ifndef ML_SCNOBJACCGPUCHECK_H
#define ML_SCNOBJACCGPUCHECK_H

namespace mm { class Vec3; }

namespace ml {
// a GPU visibility check object (ml::DrGpuCheckObj, table 0x7100B7D6C8, implements it: release is its slot 2;
// this table is not in the module)
class DrGpuCheckBase {
public:
    virtual ~DrGpuCheckBase() {}  // slot 0
    virtual void release() = 0;  // slot 2
    virtual bool isRender() const = 0;  // slot 3
    virtual void setPause(bool) = 0;  // slot 4
    virtual void setPos(const mm::Vec3& pos, float radius) = 0;  // slot 5
};
// access to a GPU visibility check (fw::VisibleObject's)
class ScnObjAccGpuCheck {
public:
    static DrGpuCheckBase* create(unsigned int arg);  // a check object made by DrCreator
    ScnObjAccGpuCheck(DrGpuCheckBase* check);
    bool isRender() const;
    void setPos(const mm::Vec3& pos, float radius);
    DrGpuCheckBase* m_check;  // the constructor's
};
}  // namespace ml

#endif

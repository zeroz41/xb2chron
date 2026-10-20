#ifndef CLASSES_ML_DRGPUCHECKOBJ_H
#define CLASSES_ML_DRGPUCHECKOBJ_H

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7D6C8
class DrGpuCheckObj {
public:
    virtual ~DrGpuCheckObj();  // slot 0
    virtual void release();  // slot 2
    virtual void isRender() const;  // slot 3
    virtual void setPause(bool);  // slot 4
    virtual void setPos(mm::Vec3 const&, float);  // slot 5
    virtual void setWorldPos(mm::Vec3 const&, float);  // slot 6
    virtual void isDeleteCall() const;  // slot 7
    virtual void update();  // slot 8
    virtual void render();  // slot 9
};
}  // namespace ml

#endif

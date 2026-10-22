#ifndef CLASSES_NAVI_NVMSHACOBJBASE_H
#define CLASSES_NAVI_NVMSHACOBJBASE_H

namespace mm { class Vec3; }

namespace navi {
// table none (its derived classes')
class NvmshAcObjBase {
public:
    virtual ~NvmshAcObjBase();  // slot 0
    virtual const mm::Vec3& getMoveVec() const;  // slot 2
    virtual void setBeginPos(mm::Vec3 const&);  // slot 3
    virtual void setEndPos(mm::Vec3 const&);  // slot 4
    virtual void setBeginRadius(float);  // slot 5
    virtual void setEndRadius(float);  // slot 6
    virtual void setBeginSeachRadius(float);  // slot 7
    virtual void setEndSeachRadius(float);  // slot 8
    virtual void setBeginHeight(float, float);  // slot 9
    virtual void setEndHeight(float, float);  // slot 10
    virtual void setMeshNum(int);  // slot 11
    virtual void getMeshNum() const;  // slot 12
    virtual void setMoveSpd(float);  // slot 13
};
}  // namespace navi

#endif

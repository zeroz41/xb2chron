#ifndef CLASSES_NAVI_NVMSHACOBJBASE_H
#define CLASSES_NAVI_NVMSHACOBJBASE_H

#include "mm/Vec3.h"

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
    virtual int getMeshNum() const;  // slot 12
    virtual void setMoveSpd(float);  // slot 13

    // 1 while it holds a move vector to read (gf::canGetMoveVec); the name is not the original's
    int m_state;
    unsigned char pad_c[0x4];
    // bit 1: it holds a move vector (gf::canGetMoveVec requires it, TaskFieldFollowTarget::testCondition too)
    unsigned int m_flags;
    // The field names follow the accessors that read and write them (not the original's).
    unsigned char pad_14[0x4F];
    signed char m_meshNum;  // getMeshNum
    bool m_isMeshNum;  // setMeshNum: whether the number it was given is positive
    unsigned char pad_65[0x4B];
    mm::Vec3 m_beginPos;  // setBeginPos
    float m_beginHeight[2];  // setBeginHeight
    float m_beginRadius;  // setBeginRadius
    float m_beginSeachRadius;  // setBeginSeachRadius
    unsigned char pad_D0[0x10];
    mm::Vec3 m_endPos;  // setEndPos
    float m_endHeight[2];  // setEndHeight
    float m_endRadius;  // setEndRadius
    float m_endSeachRadius;  // setEndSeachRadius
    unsigned char pad_100[0x50];
    mm::Vec3 m_moveVec;  // getMoveVec
    float m_moveSpd;  // setMoveSpd
};
}  // namespace navi

#endif

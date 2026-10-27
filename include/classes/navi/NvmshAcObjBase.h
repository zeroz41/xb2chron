#ifndef CLASSES_NAVI_NVMSHACOBJBASE_H
#define CLASSES_NAVI_NVMSHACOBJBASE_H

#include "mm/Vec3.h"

namespace navi {
// table none (its derived classes')
class NvmshAcObjBase {
public:
    // trivial and inline: NvmshAcObjBaseGbl's destructor is an empty function
    virtual ~NvmshAcObjBase() {}  // slot 0
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

    // The constructor and reset() are inline: the managers construct the objects in place (NvmshAcMan's
    // constructor) and reset them (NvmshAcMan::objectUpdate, createObj, NvmshAcObjBaseGbl::release).
    NvmshAcObjBase()
        : m_prev(nullptr), m_next(nullptr), m_status(0), m_work(nullptr), m_workSize(0), m_route54(0), m_flag5E(0),
          m_request(0), m_beginPos(0.0f, 0.0f, 0.0f), m_beginHeight{3.0f, 20.0f}, m_beginRadius(1.0f),
          m_beginSeachRadius(3.0f), m_endPos(0.0f, 0.0f, 1.0f), m_endHeight{3.0f, 20.0f}, m_endRadius(1.0f),
          m_endSeachRadius(3.0f), m_vec110(0.0f, 0.0f, 0.0f), m_vec120(0.0f, 0.0f, 0.0f), m_vec130(0.0f, 0.0f, 1.0f),
          m_moveVec(0.0f, 0.0f, 1.0f), m_moveSpd(0.0f) {
        reset();
    }
    // back to the unused state; the name is not the original's
    void reset() {
        m_flags = 0x18;
        m_status = 0;
        m_route50 = 0;
        m_route52 = 0;
        m_route54 = 0;
        m_route56 = 0;
        m_route58 = 0;
        m_route5A = 0;
        m_route5C = -1;
        m_flag5E = 0;
        m_flag5F = 0;
        m_flag60 = 0;
        m_flag61 = 0;
        m_flag62 = 0;
        m_meshNum = 0;
        m_isMeshNum = false;
        m_request = 0;
        m_result = 0;
        m_moveVec.x = 0.0f;
        m_moveVec.z = 1.0f;
        m_moveVec.y = 0.0f;
    }
    // the work buffer NvmshAcMan's constructor hands each object (a slice of the resource's); the name is not the
    // original's
    void setWork(int* work, int size) {
        m_work = work;
        m_workSize = size;
        m_workCur = work;
        m_workEnd = work;
    }

    // 1 while it holds a move vector to read (gf::canGetMoveVec); the name is not the original's
    int m_state;
    int m_result;  // reset() clears it; the name is not the original's
    // bit 0: in use (NvmshAcMan::createObj sets it, objectUpdate's reset clears it); bit 1: it holds a move vector
    // (gf::canGetMoveVec requires it, TaskFieldFollowTarget::testCondition too); reset() leaves 0x18
    unsigned int m_flags;
    unsigned char pad_14[0x4];
    // NvmshAcMan's lists (the active list, the two entry lists); the names are not the original's
    NvmshAcObjBase* m_prev;
    NvmshAcObjBase* m_next;
    unsigned int m_status;  // status bits stateUpdate sets and masks; the name is not the original's
    unsigned char pad_2C[0x4];
    int* m_work;
    int m_workSize;
    unsigned char pad_3C[0x4];
    int* m_workCur;
    int* m_workEnd;
    // The field names follow the accessors that read and write them; the others are not the original's.
    short m_route50;
    short m_route52;
    short m_route54;
    short m_route56;
    short m_route58;
    short m_route5A;
    short m_route5C;
    unsigned char m_flag5E;
    unsigned char m_flag5F;
    unsigned char m_flag60;
    unsigned char m_flag61;
    unsigned char m_flag62;
    signed char m_meshNum;  // getMeshNum
    bool m_isMeshNum;  // setMeshNum: whether the number it was given is positive
    // bit 0: NvmshAcMan::releaseObj asks for the object's release; the name is not the original's
    unsigned char m_request;
    unsigned char pad_66[0x4A];
    mm::Vec3 m_beginPos;  // setBeginPos
    float m_beginHeight[2];  // setBeginHeight
    float m_beginRadius;  // setBeginRadius
    float m_beginSeachRadius;  // setBeginSeachRadius
    unsigned char pad_D0[0x10];
    mm::Vec3 m_endPos;  // setEndPos
    float m_endHeight[2];  // setEndHeight
    float m_endRadius;  // setEndRadius
    float m_endSeachRadius;  // setEndSeachRadius
    unsigned char pad_100[0x10];
    mm::Vec3 m_vec110;
    mm::Vec3 m_vec120;
    mm::Vec3 m_vec130;
    unsigned char pad_140[0x10];
    mm::Vec3 m_moveVec;  // getMoveVec
    float m_moveSpd;  // setMoveSpd
    unsigned char pad_164[0xC];
};
}  // namespace navi

#endif

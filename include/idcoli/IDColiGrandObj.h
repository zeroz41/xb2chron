#ifndef IDCOLI_IDCOLIGRANDOBJ_H
#define IDCOLI_IDCOLIGRANDOBJ_H

namespace mm { class Mat44; }

namespace idcoli {

// one moving part of a grand object (0x200 bytes: IDColiParmsGrand::getMoveObj indexes them so). Only the members
// IDColiParmsGrand/IDColiPartsMoveGrand use are declared; the field names are not the original's.
class IDColiGrdMoveObj {
public:
    void setMat(const mm::Mat44& matrix);

    unsigned char pad_0[0x1B0];
    const char* m_name;  // 0x1B0, IDColiParmsGrand::getMoveObjIdx compares it
    void* m_userData;  // 0x1B8, IDColiPartsMoveGrand::setUserData
    unsigned char pad_1c0[0x40];
};

// the destructor (its owners' destructors call it; its body is empty) and the fields IDColiParmsGrand reads; the
// field names are not the original's
class IDColiGrandObj {
public:
    ~IDColiGrandObj();

    unsigned char pad_0[0x70];
    IDColiGrdMoveObj* m_moveObjs;  // 0x70
    int m_moveObjNum;  // 0x78
};

}  // namespace idcoli

#endif

#ifndef IDCOLI_IDCOLIPARMS_H
#define IDCOLI_IDCOLIPARMS_H

namespace mm { class Mat44; class Vec3; }
#include "classes/idcoli/IDColiObjBase.h"

namespace idcoli { class IDColiGrandObj; class IDColiGrdMoveObj; class IDColiObjData; class IDColiObjPhantom; }

namespace idcoli {
// a collision attribute and state: bit numbers of IDColiObj::m_attr/m_state; no value has a name yet
enum ColiAtrr {};
enum ColiState {};

// the views fw::ColiObject builds on the stack over an IDColiObj to read and set it. The member names are not the
// original's.
class IDColiParmsBase {
public:
    IDColiParmsBase(IDColiObj* obj) : m_obj(static_cast<IDColiObjBase*>(obj)) {}
    void setPriority(int priority);
    int getPriority() const;
    void setUserData(void* userData);
    bool isAttr(ColiAtrr attr) const;
    bool isState(ColiState state) const;
    void setState(ColiState state);
    void clearState(ColiState state);
    void setMaterialBit(unsigned int bit);
    void setOffMaterialBit(unsigned int bit);
    unsigned int getOffMaterialBit() const;
    void setMatrix(const mm::Mat44& matrix);
    const mm::Vec3& getMax() const;
    const mm::Vec3& getMin() const;
    void setInstantlyMatrix(const mm::Mat44& matrix);

    IDColiObjBase* m_obj;
};

// a character's (an IDColiObjChar, built from collision data)
class IDColiParmsCharacter : public IDColiParmsBase {
public:
    IDColiParmsCharacter(IDColiObj* obj);
    void createSphere(float radius);
    void createCapsule(float height, float radius, bool flag);
    void createBox(const mm::Vec3& size, bool flag);
    void createCharacter(float height, float radius);
    void createData(const void* data);
    void setAdsorption(float adsorption);
    float getAdsorption() const;

    IDColiObjData* m_data;
};

// a data object's bones
class IDColiParmsBone {
public:
    IDColiParmsBone(IDColiObj* obj);
    int getBoneMax() const;
    const char* getBoneName(int index) const;
    void setBoneMatrix(int index, const mm::Mat44& matrix);

    IDColiObjData* m_data;
};

// a phantom's
class IDColiParmsPhantom : public IDColiParmsBase {
public:
    IDColiParmsPhantom(IDColiObj* obj);
    void createSphere(float radius);
    void createCapsule(float height, float radius);
    void createBox(const mm::Vec3& size);
    void createCharacter(float height, float radius);

    IDColiObjPhantom* m_phantom;
};

// one moving part of a grand object (IDColiParmsGrand::getMoveObj returns it)
class IDColiPartsMoveGrand {
public:
    IDColiPartsMoveGrand(IDColiGrdMoveObj* obj) : m_obj(obj) {}
    // its own copy: getMoveObj returns it through x8, as a class that is not trivially copyable is
    IDColiPartsMoveGrand(const IDColiPartsMoveGrand& other) : m_obj(other.m_obj) {}
    void setMatrix(const mm::Mat44& matrix);
    void setUserData(void* userData);

    IDColiGrdMoveObj* m_obj;
};

// a grand object's (an IDColiObjGrand)
class IDColiParmsGrand {
public:
    IDColiParmsGrand(IDColiObj* obj);
    IDColiPartsMoveGrand getMoveObj(unsigned int index);
    int getMoveObjIdx(const char* name);

    IDColiGrandObj* m_grand;
};
}  // namespace idcoli

#endif

// not proven yet: does not compile: class member cannot be redeclared
#ifndef CLASSES_IDCOLI_IDCOLIOBJPHANTOMCHECK_H
#define CLASSES_IDCOLI_IDCOLIOBJPHANTOMCHECK_H

namespace idcoli { class IDColiBaseType; }
namespace idcoli { class IDColiInput; }
namespace idcoli { class IDColiResult; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace idcoli {
// table 0x7100B7F258
class IDColiObjPhantomCheck {
public:
    virtual ~IDColiObjPhantomCheck();  // slot 0
    virtual void release();  // slot 2
    virtual void sizeUpdate();  // slot 3
    virtual void update();  // slot 4
    virtual void SweepAndPruneUpdate();  // slot 5
    virtual void consistentUpdate();  // slot 6
    virtual void isLineSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 7
    virtual void isLineBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 8
    virtual void isLineCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 9
    virtual void isLineCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 10
    virtual void isLineSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 11
    virtual void isLinePoli(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 12
    virtual void isLineInBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 13
    virtual void isLineInCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 14
    virtual void isRaySphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 15
    virtual void isRayBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 16
    virtual void isRayCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 17
    virtual void isRayCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 18
    virtual void isRaySphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 19
    virtual void isRayPoli(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 20
    virtual void isRayInBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 21
    virtual void isRayInCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 22
    virtual void isSphereSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 23
    virtual void isSphereBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 24
    virtual void isSphereCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 25
    virtual void isSphereCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 26
    virtual void isSphereSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 27
    virtual void isSpherePoli(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 28
    virtual void isSphereInBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 29
    virtual void isSphereInCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 30
    virtual void isCapsuleSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 31
    virtual void isCapsuleBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 32
    virtual void isCapsuleCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 33
    virtual void isCapsuleCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 34
    virtual void isCapsuleSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 35
    virtual void isCapsulePoli(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 36
    virtual void isCapsuleInBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 37
    virtual void isCapsuleInCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 38
    virtual void isLineSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 39
    virtual void isLineBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 40
    virtual void isLineCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 41
    virtual void isLineCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 42
    virtual void isLineSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 43
    virtual void isLinePoli(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 44
    virtual void isLineInBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 45
    virtual void isLineInCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 46
    virtual void isRaySphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 47
    virtual void isRayBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 48
    virtual void isRayCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 49
    virtual void isRayCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 50
    virtual void isRaySphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 51
    virtual void isRayPoli(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 52
    virtual void isRayInBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 53
    virtual void isRayInCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 54
    virtual void isSphereSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 55
    virtual void isSphereBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 56
    virtual void isSphereCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 57
    virtual void isSphereCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 58
    virtual void isSphereSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 59
    virtual void isSpherePoli(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 60
    virtual void isSphereInBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 61
    virtual void isSphereInCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 62
    virtual void isCapsuleSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 63
    virtual void isCapsuleBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 64
    virtual void isCapsuleCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 65
    virtual void isCapsuleCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 66
    virtual void isCapsuleSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 67
    virtual void isCapsulePoli(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 68
    virtual void isCapsuleInBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 69
    virtual void isCapsuleInCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 70
    virtual void isBoxSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 71
    virtual void isBoxBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 72
    virtual void isBoxCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 73
    virtual void isBoxCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 74
    virtual void isBoxSphere(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 75
    virtual void isBoxPoli(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 76
    virtual void isBoxBox(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 77
    virtual void isBoxCapsule(idcoli::IDColiResult&, idcoli::IDColiInput const&, void const*);  // slot 78
    virtual void createBaseSphere(void*, idcoli::IDColiBaseType&, mm::Mat44 const&, mm::Vec3 const&);  // slot 79
    virtual void createBaseBox(void*, idcoli::IDColiBaseType&, mm::Mat44 const&, mm::Vec3 const&);  // slot 80
    virtual void createBaseCapsule(void*, idcoli::IDColiBaseType&, mm::Mat44 const&, mm::Vec3 const&);  // slot 81
    virtual void createBaseCharacter(void*, idcoli::IDColiBaseType&, mm::Mat44 const&, mm::Vec3 const&);  // slot 82
    virtual void createBaseSphere(void*, idcoli::IDColiBaseType&, mm::Mat44 const&, mm::Vec3 const&);  // slot 83
    virtual void createBasePoli(void*, idcoli::IDColiBaseType&, mm::Mat44 const&, mm::Vec3 const&);  // slot 84
    virtual void createBaseInBox(void*, idcoli::IDColiBaseType&, mm::Mat44 const&, mm::Vec3 const&);  // slot 85
    virtual void createBaseInCapsule(void*, idcoli::IDColiBaseType&, mm::Mat44 const&, mm::Vec3 const&);  // slot 86
    virtual void createAaBbSphere(mm::Vec3&, mm::Vec3&, void const*);  // slot 87
    virtual void createAaBbBox(mm::Vec3&, mm::Vec3&, void const*);  // slot 88
    virtual void createAaBbCapsule(mm::Vec3&, mm::Vec3&, void const*);  // slot 89
    virtual void createAaBbCapsule(mm::Vec3&, mm::Vec3&, void const*);  // slot 90
    virtual void createAaBbSphere(mm::Vec3&, mm::Vec3&, void const*);  // slot 91
    virtual void createAaBbPoli(mm::Vec3&, mm::Vec3&, void const*);  // slot 92
    virtual void createAaBbBox(mm::Vec3&, mm::Vec3&, void const*);  // slot 93
    virtual void createAaBbCapsule(mm::Vec3&, mm::Vec3&, void const*);  // slot 94
    virtual void createBaPosSphere(mm::Vec3&, mm::Vec3&, bool&, float&, float&, void const*);  // slot 95
    virtual void createBaPosBox(mm::Vec3&, mm::Vec3&, bool&, float&, float&, void const*);  // slot 96
    virtual void createBaPosCapsule(mm::Vec3&, mm::Vec3&, bool&, float&, float&, void const*);  // slot 97
    virtual void createBaPosCapsule(mm::Vec3&, mm::Vec3&, bool&, float&, float&, void const*);  // slot 98
    virtual void createBaPosSphere(mm::Vec3&, mm::Vec3&, bool&, float&, float&, void const*);  // slot 99
    virtual void createBaPosPoli(mm::Vec3&, mm::Vec3&, bool&, float&, float&, void const*);  // slot 100
    virtual void createBaPosBox(mm::Vec3&, mm::Vec3&, bool&, float&, float&, void const*);  // slot 101
    virtual void createBaPosCapsule(mm::Vec3&, mm::Vec3&, bool&, float&, float&, void const*);  // slot 102
};
}  // namespace idcoli

#endif

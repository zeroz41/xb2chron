#ifndef IDCOLI_IDCOLIUTILCOLI_H
#define IDCOLI_IDCOLIUTILCOLI_H

namespace idcoli { class IDColiInput; }

namespace idcoli { class CLBoxWork; }
namespace idcoli { class CLCapsuleWork; }
namespace idcoli { class CLLineWork; }
namespace idcoli { class CLSphereWork; }
namespace idcoli { class IDColiResult; }

namespace idcoli {

// shape-pair collision tests without a result (Simple) and with one (Result). The input forms (input's shape
// against another object's) fill the tables s_CallSphere etc. that IDColiObjCharCheck/IDColiObjPhantomCheck call
// through. The return type is not in the symbols (both return 0 or 1; bool assumed).
class IDColiUtilColiSimple {
public:
    // indexed by the other object's IDColiBaseType (this unit's .data)
    static bool (*s_CallLine[8])(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool (*s_CallRay[8])(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool (*s_CallSphere[8])(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool (*s_CallCapsule[8])(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool (*s_CallBox[8])(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isSphereBox(IDColiResult& result, const CLSphereWork* sphere, const CLBoxWork* box);
    static bool isCapsuleBox(IDColiResult& result, const CLCapsuleWork* capsule, const CLBoxWork* box);
    static bool isCapsuleInBox(IDColiResult& result, const CLCapsuleWork* capsule, const CLBoxWork* box);
    static bool isPartsLineBox(IDColiResult& result, const CLLineWork* line, const void* pOther, bool inside);
    static bool isPartsLineCapsule(IDColiResult& result, const CLLineWork* line, const void* pOther, bool inside);

    static bool isSphereBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isSpherePoli(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isCapsuleBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isCapsuleInBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isCapsulePoli(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isBoxSphere(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isBoxBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isBoxCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isBoxPoli(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isLineBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isLineCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isLinePoli(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isLineInBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isLineInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isRayBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isRayInBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isRayCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isRayInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isRayPoli(IDColiResult& result, const IDColiInput& input, const void* pOther);
};

class IDColiUtilColiResult {
public:
    // indexed by the other object's IDColiBaseType (this unit's .data)
    static bool (*s_CallLine[8])(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool (*s_CallRay[8])(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool (*s_CallSphere[8])(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool (*s_CallCapsule[8])(IDColiResult& result, const IDColiInput& input, const void* pOther);
    // the last bool: a line in a box/capsule test sets it (isLineInBox/isLineInCapsule); the names are not the
    // original's
    static bool isPartsLineSphere(IDColiResult& result, const CLLineWork* line, const void* pOther, bool ray);
    static bool isPartsLineBox(IDColiResult& result, const CLLineWork* line, const void* pOther, bool ray, bool inside);
    static bool isPartsLineCapsule(IDColiResult& result, const CLLineWork* line, const void* pOther, bool ray,
                                   bool inside);

    static bool isSpherePoli(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isCapsulePoli(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isLineSphere(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isLineBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isLineInBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isLineCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isLineInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isLinePoli(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isRaySphere(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isRayBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isRayInBox(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isRayCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isRayInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther);
    static bool isRayPoli(IDColiResult& result, const IDColiInput& input, const void* pOther);
};

}  // namespace idcoli

#endif

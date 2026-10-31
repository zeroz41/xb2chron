#include "idcoli/IDColiUtilColi.h"
#include "idcoli/IDColiInput.h"
#include "idcoli/IDColiPrimitive.h"
#include "idcoli/IDColiShapeWork.h"

namespace idcoli {

bool IDColiUtilColiResult::isSpherePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiResult::isCapsulePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiResult::isLineSphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineSphere(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiResult::isLineBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, false);
}

bool IDColiUtilColiResult::isLineInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, true);
}

bool IDColiUtilColiResult::isLineCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, false);
}

bool IDColiUtilColiResult::isLineInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false, true);
}

bool IDColiUtilColiResult::isLinePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiResult::isRaySphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineSphere(result, &ray->m_lines[0], pOther, false)) return true;
    return isPartsLineSphere(result, &ray->m_lines[1], pOther, true);
}

bool IDColiUtilColiResult::isRayBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineBox(result, &ray->m_lines[0], pOther, false, false)) return true;
    return isPartsLineBox(result, &ray->m_lines[1], pOther, true, false);
}

bool IDColiUtilColiResult::isRayInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineBox(result, &ray->m_lines[0], pOther, false, true)) return true;
    return isPartsLineBox(result, &ray->m_lines[1], pOther, true, true);
}

bool IDColiUtilColiResult::isRayCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineCapsule(result, &ray->m_lines[0], pOther, false, false)) return true;
    return isPartsLineCapsule(result, &ray->m_lines[1], pOther, true, false);
}

bool IDColiUtilColiResult::isRayInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineCapsule(result, &ray->m_lines[0], pOther, false, true)) return true;
    return isPartsLineCapsule(result, &ray->m_lines[1], pOther, true, true);
}

bool IDColiUtilColiResult::isRayPoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isSphereBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isSphereBox(result, static_cast<const CLSphereWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isSpherePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isCapsuleBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isCapsuleBox(result, static_cast<const CLCapsuleWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isCapsuleInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isCapsuleInBox(result, static_cast<const CLCapsuleWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isCapsulePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isBoxSphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isSphereBox(result, static_cast<const CLSphereWork*>(pOther), static_cast<const CLBoxWork*>(input.getShape()));
}

bool IDColiUtilColiSimple::isBoxBox(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isBoxCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isCapsuleBox(result, static_cast<const CLCapsuleWork*>(pOther), static_cast<const CLBoxWork*>(input.getShape()));
}

bool IDColiUtilColiSimple::isBoxPoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isLineBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiSimple::isLineCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiSimple::isLinePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isLineInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineBox(result, static_cast<const CLLineWork*>(input.getShape()), pOther, true);
}

bool IDColiUtilColiSimple::isLineInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isPartsLineCapsule(result, static_cast<const CLLineWork*>(input.getShape()), pOther, false);
}

bool IDColiUtilColiSimple::isRayBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineBox(result, &ray->m_lines[0], pOther, false)) return true;
    return isPartsLineBox(result, &ray->m_lines[1], pOther, false);
}

bool IDColiUtilColiSimple::isRayInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineBox(result, &ray->m_lines[0], pOther, true)) return true;
    return isPartsLineBox(result, &ray->m_lines[1], pOther, true);
}

bool IDColiUtilColiSimple::isRayCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineCapsule(result, &ray->m_lines[0], pOther, false)) return true;
    return isPartsLineCapsule(result, &ray->m_lines[1], pOther, false);
}

bool IDColiUtilColiSimple::isRayInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    if (isPartsLineCapsule(result, &ray->m_lines[0], pOther, true)) return true;
    return isPartsLineCapsule(result, &ray->m_lines[1], pOther, true);
}

bool IDColiUtilColiSimple::isRayPoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

}  // namespace idcoli

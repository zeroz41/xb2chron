#include "idcoli/IDColiUtilColi.h"
#include "idcoli/IDColiInput.h"
#include "idcoli/IDColiPrimitive.h"
#include "idcoli/IDColiShapeWork.h"
#include "classes/idcoli/IDColiObjGrdChar.h"

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

void IDColiPrimitive::calcBoxAaBb(CLBoxWork* box) {
    mm::Vec3 corners[8] = {
        mm::Vec3(box->m_size.x, box->m_size.y, box->m_size.z),    mm::Vec3(box->m_size.x, box->m_size.y, -box->m_size.z),
        mm::Vec3(-box->m_size.x, box->m_size.y, box->m_size.z),   mm::Vec3(-box->m_size.x, box->m_size.y, -box->m_size.z),
        mm::Vec3(box->m_size.x, -box->m_size.y, box->m_size.z),   mm::Vec3(box->m_size.x, -box->m_size.y, -box->m_size.z),
        mm::Vec3(-box->m_size.x, -box->m_size.y, box->m_size.z),  mm::Vec3(-box->m_size.x, -box->m_size.y, -box->m_size.z),
    };
    box->m_max.x = box->m_max.y = box->m_max.z = -100000.0f;
    box->m_min.x = box->m_min.y = box->m_min.z = 100000.0f;
    for (int i = 0; i < 8; i++) {
        mm::Vec3 pos(corners[i].dot(box->m_axes[0]), corners[i].dot(box->m_axes[1]), corners[i].dot(box->m_axes[2]));
        if (box->m_max.x < pos.x) box->m_max.x = pos.x;
        if (box->m_min.x > pos.x) box->m_min.x = pos.x;
        if (box->m_max.y < pos.y) box->m_max.y = pos.y;
        if (box->m_min.y > pos.y) box->m_min.y = pos.y;
        if (box->m_max.z < pos.z) box->m_max.z = pos.z;
        if (box->m_min.z > pos.z) box->m_min.z = pos.z;
    }
    box->m_max += box->m_center;
    box->m_min += box->m_center;
}

void IDColiPrimitive::createBaseSphere(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size) {
    CLSphereWork* sphere = static_cast<CLSphereWork*>(base);
    type = IDCOLI_BASE_SPHERE;
    mm::Vec3 axis(matrix.m[0][0] + matrix.m[1][0] + matrix.m[2][0], matrix.m[0][1] + matrix.m[1][1] + matrix.m[2][1],
                  matrix.m[0][2] + matrix.m[1][2] + matrix.m[2][2]);
    float radius = axis.length() * IDColiObj::OBJ_CALC_RADIUS;
    sphere->m_radius = size.x * radius;
    sphere->m_center = matrix.getTrans();
}

void IDColiPrimitive::createBaseBox(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size) {
    calcBaseBoxSetup(static_cast<CLBoxWork*>(base), matrix, size);
    type = IDCOLI_BASE_BOX;
}

void IDColiPrimitive::createBasePoli(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3&) {
    IDColiObjGrdChar::Part* part = *static_cast<IDColiObjGrdChar::Part**>(base);
    calcPosDataSetup(&part->m_posData, matrix, part->m_corners[0], part->m_corners[1]);
    type = IDCOLI_BASE_POLI;
}

void IDColiPrimitive::createAaBbSphere(mm::Vec3& max, mm::Vec3& min, const void* shape) {
    const CLSphereWork* sphere = static_cast<const CLSphereWork*>(shape);
    float value;
    value = sphere->m_center.x + sphere->m_radius;
    if (max.x < value) max.x = value;
    value = sphere->m_center.x - sphere->m_radius;
    if (min.x > value) min.x = value;
    value = sphere->m_center.y + sphere->m_radius;
    if (max.y < value) max.y = value;
    value = sphere->m_center.y - sphere->m_radius;
    if (min.y > value) min.y = value;
    value = sphere->m_center.z + sphere->m_radius;
    if (max.z < value) max.z = value;
    value = sphere->m_center.z - sphere->m_radius;
    if (min.z > value) min.z = value;
}

void IDColiPrimitive::createAaBbBox(mm::Vec3& max, mm::Vec3& min, const void* shape) {
    const CLBoxWork* box = static_cast<const CLBoxWork*>(shape);
    if (max.x < box->m_max.x) max.x = box->m_max.x;
    if (min.x > box->m_min.x) min.x = box->m_min.x;
    if (max.y < box->m_max.y) max.y = box->m_max.y;
    if (min.y > box->m_min.y) min.y = box->m_min.y;
    if (max.z < box->m_max.z) max.z = box->m_max.z;
    if (min.z > box->m_min.z) min.z = box->m_min.z;
}

void IDColiPrimitive::createAaBbCapsule(mm::Vec3& max, mm::Vec3& min, const void* shape) {
    const CLCapsuleWork* capsule = static_cast<const CLCapsuleWork*>(shape);
    if (max.x < capsule->m_max.x) max.x = capsule->m_max.x;
    if (min.x > capsule->m_min.x) min.x = capsule->m_min.x;
    if (max.y < capsule->m_max.y) max.y = capsule->m_max.y;
    if (min.y > capsule->m_min.y) min.y = capsule->m_min.y;
    if (max.z < capsule->m_max.z) max.z = capsule->m_max.z;
    if (min.z > capsule->m_min.z) min.z = capsule->m_min.z;
}

void IDColiPrimitive::createAaBbPoli(mm::Vec3&, mm::Vec3&, const void*) {}

void IDColiPrimitive::createBaPosSphere(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                                        const void* shape) {
    const CLSphereWork* sphere = static_cast<const CLSphereWork*>(shape);
    pos = sphere->m_center;
    radius = sphere->m_radius;
    height = sphere->m_radius + sphere->m_radius;
    flag = false;
    offset = mm::Vec3(0.0f, 0.0f, 0.0f);
}

void IDColiPrimitive::createBaPosBox(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                                     const void* shape) {
    const CLBoxWork* box = static_cast<const CLBoxWork*>(shape);
    pos = box->m_center;
    radius = box->m_size.x;
    height = box->m_size.y;
    flag = false;
    offset = mm::Vec3(0.0f, 0.0f, 0.0f);
}

void IDColiPrimitive::createBaPosCapsule(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                                         const void* shape) {
    const CLCapsuleWork* capsule = static_cast<const CLCapsuleWork*>(shape);
    pos = capsule->m_pos;
    radius = capsule->m_radius;
    height = ::sqrtf(capsule->m_lengthSq) + (radius + radius);
    flag = true;
    offset = capsule->m_offset;
}

void IDColiPrimitive::createBaPosPoli(mm::Vec3& pos, mm::Vec3& offset, bool& flag, float& radius, float& height,
                                      const void* shape) {
    const IDColiObjGrdChar::Part* part = *static_cast<const IDColiObjGrdChar::Part* const*>(shape);
    pos = mm::Vec3(part->m_posData.m_matrix.m[0][3], part->m_posData.m_matrix.m[1][3],
                   part->m_posData.m_matrix.m[2][3]);
    radius = (part->m_posData.m_max.x - part->m_posData.m_min.x) * 0.5f;
    height = radius + radius;
    flag = false;
    offset = mm::Vec3(0.0f, 0.0f, 0.0f);
}

}  // namespace idcoli

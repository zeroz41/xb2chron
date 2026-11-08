#include <string.h>

#include "idcoli/IDColiUtilColi.h"
#include "idcoli/IDColiInput.h"
#include "idcoli/IDColiInputUtil.h"
#include "idcoli/IDColiPrimitive.h"
#include "idcoli/IDColiShapeWork.h"
#include "classes/idcoli/IDColiObjGrdChar.h"
#include "idcoli/IDColiResult.h"
#include "classes/fw/ColiCheckCallback.h"

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

bool IDColiUtilColiSimple::isSphereSphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLSphereWork* sphere = static_cast<const CLSphereWork*>(input.getShape());
    const CLSphereWork* other = static_cast<const CLSphereWork*>(pOther);
    mm::Vec3 dir = sphere->m_center - other->m_center;
    float radius = sphere->m_radius + other->m_radius;
    if (dir.dot(dir) > radius * radius) return false;
    if (result.m_callback) result.m_callback->coli_callback(result.m_obj);
    return true;
}

bool IDColiUtilColiSimple::isSphereBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isSphereBox(result, static_cast<const CLSphereWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isSphereCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLSphereWork* sphere = static_cast<const CLSphereWork*>(input.getShape());
    const CLCapsuleWork* capsule = static_cast<const CLCapsuleWork*>(pOther);
    if (capsule->m_max.x + sphere->m_radius < sphere->m_center.x) return false;
    if (capsule->m_min.x - sphere->m_radius > sphere->m_center.x) return false;
    if (sphere->m_radius + capsule->m_max.z < sphere->m_center.z) return false;
    if (capsule->m_min.z - sphere->m_radius > sphere->m_center.z) return false;
    if (sphere->m_radius + capsule->m_max.y < sphere->m_center.y) return false;
    if (capsule->m_min.y - sphere->m_radius > sphere->m_center.y) return false;
    mm::Vec3 dir = sphere->m_center - capsule->m_pos;
    float t = dir.dot(capsule->m_offset) * capsule->m_invLengthSq;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    dir -= capsule->m_offset * t;
    float sum = sphere->m_radius + capsule->m_radius;
    if (dir.dot(dir) > sum * sum) return false;
    if (result.m_callback) result.m_callback->coli_callback(result.m_obj);
    return true;
}

bool IDColiUtilColiSimple::isSphereInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLSphereWork* sphere = static_cast<const CLSphereWork*>(input.getShape());
    const CLCapsuleWork* capsule = static_cast<const CLCapsuleWork*>(pOther);
    if (capsule->m_max.x + sphere->m_radius < sphere->m_center.x) return false;
    if (capsule->m_min.x - sphere->m_radius > sphere->m_center.x) return false;
    if (sphere->m_radius + capsule->m_max.z < sphere->m_center.z) return false;
    if (capsule->m_min.z - sphere->m_radius > sphere->m_center.z) return false;
    if (sphere->m_radius + capsule->m_max.y < sphere->m_center.y) return false;
    if (capsule->m_min.y - sphere->m_radius > sphere->m_center.y) return false;
    mm::Vec3 dir = sphere->m_center - capsule->m_pos;
    float t = dir.dot(capsule->m_offset) * capsule->m_invLengthSq;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    mm::Vec3 offset = capsule->m_offset * t;
    dir -= offset;
    float lengthSq = dir.dot(dir);
    if (lengthSq > capsule->m_radius * capsule->m_radius) return false;
    if (lengthSq <= 1e-6f) return false;
    float length = ::sqrtf(lengthSq);
    mm::Vec3 normal = dir * (1.0f / length);
    mm::Vec3 pos = offset + capsule->m_radius * normal;
    pos += capsule->m_pos;
    mm::Vec3 diff = sphere->m_center - pos;
    float distSq = diff.dot(diff);
    float radiusSq = sphere->m_radius * sphere->m_radius;
    if (distSq <= 1e-6f || distSq > radiusSq) return false;
    if (result.m_callback) result.m_callback->coli_callback(result.m_obj);
    return true;
}

bool IDColiUtilColiSimple::isSpherePoli(IDColiResult&, const IDColiInput&, const void*) { return false; }

bool IDColiUtilColiSimple::isCapsuleSphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLCapsuleWork* capsule = static_cast<const CLCapsuleWork*>(input.getShape());
    const CLSphereWork* sphere = static_cast<const CLSphereWork*>(pOther);
    if (capsule->m_max.x + sphere->m_radius < sphere->m_center.x) return false;
    if (capsule->m_min.x - sphere->m_radius > sphere->m_center.x) return false;
    if (sphere->m_radius + capsule->m_max.z < sphere->m_center.z) return false;
    if (capsule->m_min.z - sphere->m_radius > sphere->m_center.z) return false;
    if (sphere->m_radius + capsule->m_max.y < sphere->m_center.y) return false;
    if (capsule->m_min.y - sphere->m_radius > sphere->m_center.y) return false;
    mm::Vec3 dir = sphere->m_center - capsule->m_pos;
    float t = dir.dot(capsule->m_offset) * capsule->m_invLengthSq;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    dir -= capsule->m_offset * t;
    float sum = sphere->m_radius + capsule->m_radius;
    if (dir.dot(dir) > sum * sum) return false;
    if (result.m_callback) result.m_callback->coli_callback(result.m_obj);
    return true;
}

bool IDColiUtilColiSimple::isCapsuleBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isCapsuleBox(result, static_cast<const CLCapsuleWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isCapsuleInBox(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    return isCapsuleInBox(result, static_cast<const CLCapsuleWork*>(input.getShape()), static_cast<const CLBoxWork*>(pOther));
}

bool IDColiUtilColiSimple::isCapsuleCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLCapsuleWork* capsule = static_cast<const CLCapsuleWork*>(input.getShape());
    const CLCapsuleWork* other = static_cast<const CLCapsuleWork*>(pOther);
    if (capsule->m_max.x < other->m_min.x) return false;
    if (capsule->m_min.x > other->m_max.x) return false;
    if (capsule->m_max.z < other->m_min.z) return false;
    if (capsule->m_min.z > other->m_max.z) return false;
    if (capsule->m_max.y < other->m_min.y) return false;
    if (capsule->m_min.y > other->m_max.y) return false;
    mm::Vec3 nearPos;
    mm::Vec3 otherNearPos;
    IDColiUtilMath::getNearLineToLine(nearPos, otherNearPos, capsule->m_pos, capsule->m_end, other->m_pos,
                                      other->m_end);
    mm::Vec3 dir = nearPos - otherNearPos;
    float radius = capsule->m_radius + other->m_radius;
    if (dir.dot(dir) > radius * radius) return false;
    if (result.m_callback) result.m_callback->coli_callback(result.m_obj);
    return true;
}

bool IDColiUtilColiSimple::isCapsuleInCapsule(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLCapsuleWork* capsule = static_cast<const CLCapsuleWork*>(input.getShape());
    const CLCapsuleWork* other = static_cast<const CLCapsuleWork*>(pOther);
    // the lower end of the capsule
    const mm::Vec3& center = capsule->m_pos.y > capsule->m_end.y ? capsule->m_end : capsule->m_pos;
    if (other->m_max.x + capsule->m_radius < center.x) return false;
    if (other->m_min.x - capsule->m_radius > center.x) return false;
    if (capsule->m_radius + other->m_max.z < center.z) return false;
    if (other->m_min.z - capsule->m_radius > center.z) return false;
    if (capsule->m_radius + other->m_max.y < center.y) return false;
    if (other->m_min.y - capsule->m_radius > center.y) return false;
    mm::Vec3 dir = center - other->m_pos;
    float t = dir.dot(other->m_offset) * other->m_invLengthSq;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    mm::Vec3 offset = other->m_offset * t;
    dir -= offset;
    float lengthSq = dir.dot(dir);
    if (lengthSq > other->m_radius * other->m_radius) return false;
    if (lengthSq <= 1e-6f) return false;
    float length = ::sqrtf(lengthSq);
    mm::Vec3 normal = dir * (1.0f / length);
    mm::Vec3 pos = offset + other->m_radius * normal;
    pos += other->m_pos;
    mm::Vec3 diff = center - pos;
    float distSq = diff.dot(diff);
    float radiusSq = capsule->m_radius * capsule->m_radius;
    if (distSq <= 1e-6f || distSq > radiusSq) return false;
    if (result.m_callback) result.m_callback->coli_callback(result.m_obj);
    return true;
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

bool IDColiUtilColiSimple::isLineSphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLLineWork* line = static_cast<const CLLineWork*>(input.getShape());
    const CLSphereWork* sphere = static_cast<const CLSphereWork*>(pOther);
    mm::Vec3 dir = line->m_start - sphere->m_center;
    float b = dir.dot(line->m_unitDir);
    float c = dir.dot(dir) - sphere->m_radius * sphere->m_radius;
    if (b >= 0.0f && c >= 0.0f) return false;
    float disc = b * b - c;
    if (disc <= 0.0f) return false;
    float t = -b - ::sqrtf(disc);
    if (t < 0.0f) return false;
    if (line->m_length < t) return false;
    if (result.m_callback) result.m_callback->coli_callback(result.m_obj);
    return true;
}

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

bool IDColiUtilColiSimple::isRaySphere(IDColiResult& result, const IDColiInput& input, const void* pOther) {
    const CLRayWork* ray = static_cast<const CLRayWork*>(input.getShape());
    const CLSphereWork* sphere = static_cast<const CLSphereWork*>(pOther);
    auto isHit = [&result, sphere](const CLLineWork* line) -> bool {
        mm::Vec3 dir = line->m_start - sphere->m_center;
        float b = dir.dot(line->m_unitDir);
        float c = dir.dot(dir) - sphere->m_radius * sphere->m_radius;
        if (b >= 0.0f && c >= 0.0f) return false;
        float disc = b * b - c;
        if (disc <= 0.0f) return false;
        float t = -b - ::sqrtf(disc);
        if (t < 0.0f) return false;
        if (line->m_length < t) return false;
        if (result.m_callback) result.m_callback->coli_callback(result.m_obj);
        return true;
    };
    if (isHit(&ray->m_lines[0])) return true;
    return isHit(&ray->m_lines[1]);
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

void IDColiInputUtil::getSphere(IDColiInput& out, const mm::Vec3& pos, float radius, bool) {
    out.m_pos = pos;
    out.m_lengthMax = radius;
    out.m_lengthMin = radius * radius;
    out.m_instSizeMin = 0.0f;
    out.m_max.x = pos.x + radius;
    out.m_max.y = pos.y + radius;
    out.m_max.z = pos.z + radius;
    out.m_min.x = pos.x - radius;
    out.m_min.y = pos.y - radius;
    out.m_min.z = pos.z - radius;
    out.m_intMax[0] = ::ceilf(out.m_max.x);
    out.m_intMax[1] = ::ceilf(out.m_max.y);
    out.m_intMax[2] = ::ceilf(out.m_max.z);
    out.m_intMin[0] = ::floorf(out.m_min.x);
    out.m_intMin[1] = ::floorf(out.m_min.y);
    out.m_intMin[2] = ::floorf(out.m_min.z);
    CLSphereWork* sphere = static_cast<CLSphereWork*>(out.getShape());
    sphere->m_center = out.m_pos;
    sphere->m_radius = radius;
}

void IDColiInputUtil::getRay(IDColiInput& out, const mm::Vec3& start, const mm::Vec3& dir, float lengthMax,
                             float lengthMin, bool) {
    out.m_start = start;
    out.m_end = dir;
    out.m_lengthMax = lengthMax;
    out.m_lengthMin = lengthMin;
    out.m_length = 1.0f;
    out.m_instSizeMin = 0.0f;
    mm::Vec3 far = start + dir * lengthMax;
    mm::Vec3 near = start + dir * lengthMin;
    if (far.x > near.x) {
        out.m_max.x = far.x;
        out.m_min.x = near.x;
    } else {
        out.m_max.x = near.x;
        out.m_min.x = far.x;
    }
    if (far.y > near.y) {
        out.m_max.y = far.y;
        out.m_min.y = near.y;
    } else {
        out.m_max.y = near.y;
        out.m_min.y = far.y;
    }
    if (far.z > near.z) {
        out.m_max.z = far.z;
        out.m_min.z = near.z;
    } else {
        out.m_max.z = near.z;
        out.m_min.z = far.z;
    }
    out.m_pos = start;
    out.m_dir = dir;
    out.m_intMax[0] = ::ceilf(out.m_max.x);
    out.m_intMax[1] = ::ceilf(out.m_max.y);
    out.m_intMax[2] = ::ceilf(out.m_max.z);
    out.m_intMin[0] = ::floorf(out.m_min.x);
    out.m_intMin[1] = ::floorf(out.m_min.y);
    out.m_intMin[2] = ::floorf(out.m_min.z);
    out.m_lineHalf = (far - near) * 0.5f;
    out.m_lineCenter = near + out.m_lineHalf;
    out.m_lineHalfAbs.x = ::fabsf(out.m_lineHalf.x) + 1e-6f;
    out.m_lineHalfAbs.y = ::fabsf(out.m_lineHalf.y) + 1e-6f;
    out.m_lineHalfAbs.z = ::fabsf(out.m_lineHalf.z) + 1e-6f;
    IDColiPrimitive::createRay(*static_cast<CLRayWork*>(out.getShape()), start, dir, lengthMax, -lengthMin);
}

void IDColiPrimitive::createRay(CLRayWork& ray, const mm::Vec3& start, const mm::Vec3& dir, float lengthMax,
                                float lengthMin) {
    ray.m_lines[0].m_dir.x = dir.x * lengthMax;
    ray.m_lines[0].m_dir.y = dir.y * lengthMax;
    ray.m_lines[0].m_dir.z = dir.z * lengthMax;
    ray.m_lines[1].m_dir.x = dir.x * -lengthMin;
    ray.m_lines[1].m_dir.y = dir.y * -lengthMin;
    ray.m_lines[1].m_dir.z = dir.z * -lengthMin;
    ray.m_lines[0].m_unitDir = dir;
    ray.m_lines[1].m_unitDir = mm::Vec3(-dir.x, -dir.y, -dir.z);
    ray.m_lines[0].m_length = lengthMax;
    ray.m_lines[1].m_length = lengthMin;
    for (int i = 0; i < 2; i++) {
        CLLineWork& line = ray.m_lines[i];
        line.m_end.x = start.x + line.m_dir.x;
        line.m_end.y = start.y + line.m_dir.y;
        line.m_end.z = start.z + line.m_dir.z;
        line.m_start = start;
        line.m_lengthSq = line.m_dir.dot(line.m_dir);
        if (line.m_start.x > line.m_end.x) {
            line.m_max.x = line.m_start.x;
            line.m_min.x = line.m_end.x;
        } else {
            line.m_max.x = line.m_end.x;
            line.m_min.x = line.m_start.x;
        }
        if (line.m_start.y > line.m_end.y) {
            line.m_max.y = line.m_start.y;
            line.m_min.y = line.m_end.y;
        } else {
            line.m_max.y = line.m_end.y;
            line.m_min.y = line.m_start.y;
        }
        if (line.m_start.z > line.m_end.z) {
            line.m_max.z = line.m_start.z;
            line.m_min.z = line.m_end.z;
        } else {
            line.m_max.z = line.m_end.z;
            line.m_min.z = line.m_start.z;
        }
    }
}

void IDColiInputUtil::getBox(IDColiInput& out, const CLBoxWork& box) {
    memcpy(out.getShape(), &box, sizeof(CLBoxWork));
    out.m_max = box.m_max;
    out.m_min = box.m_min;
    out.m_instSizeMin = 0.0f;
    out.m_intMax[0] = ::ceilf(box.m_max.x);
    out.m_intMax[1] = ::ceilf(box.m_max.y);
    out.m_intMax[2] = ::ceilf(box.m_max.z);
    out.m_intMin[0] = ::floorf(box.m_min.x);
    out.m_intMin[1] = ::floorf(box.m_min.y);
    out.m_intMin[2] = ::floorf(box.m_min.z);
}

void IDColiUtilMath::getNearLineToPoint(mm::Vec3& out, const mm::Vec3& start, const mm::Vec3& end,
                                        const mm::Vec3& point) {
    mm::Vec3 dir = end - start;
    float lengthSq = dir.dot(dir);
    float t = dir.dot(point - start) / lengthSq;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    out = dir * t;
    out.x = start.x + out.x;
    out.y = start.y + out.y;
    out.z = start.z + out.z;
}

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

void IDColiPrimitive::createSubBaseCharacter(void* base, IDColiBaseType& type, const mm::Mat44& matrix,
                                             const mm::Vec3& size, bool flag) {
    CLSubCharacterWork* work = static_cast<CLSubCharacterWork*>(base);
    mm::Vec3 axis(matrix.m[0][0] + matrix.m[1][0] + matrix.m[2][0], matrix.m[0][1] + matrix.m[1][1] + matrix.m[2][1],
                  matrix.m[0][2] + matrix.m[1][2] + matrix.m[2][2]);
    float scale = axis.length() * IDColiObj::OBJ_CALC_RADIUS;
    float radius = size.x * scale;
    float height = scale * size.y;
    if (!(height + radius * -2.0f <= 0.01f)) {
        work->m_radius = radius;
        if (flag) {
            work->m_move = mm::Vec3(0.0f, 0.0f, 0.0f);
            work->m_pos = matrix.getTrans();
            work->m_pos.y += height;
        } else {
            mm::Vec3 pos = matrix.getTrans();
            pos.y += height;
            work->m_move.x = pos.x - work->m_pos.x;
            work->m_move.y = pos.y - work->m_pos.y;
            work->m_move.z = pos.z - work->m_pos.z;
            float lengthSq = work->m_move.x * work->m_move.x + work->m_move.y * work->m_move.y;
            if (work->m_move.z * work->m_move.z + lengthSq >= 4.0f) work->m_move = mm::Vec3(0.0f, 0.0f, 0.0f);
            work->m_pos = pos;
        }
        work->m_end = work->m_pos;
        work->m_end.y -= height;
        calcCapsuleSetup(work);
        type = IDCOLI_BASE_CHARACTER;
    } else {
        CLSphereWork* sphere = static_cast<CLSphereWork*>(base);
        sphere->m_radius = radius;
        if (flag) {
            work->m_move = mm::Vec3(0.0f, 0.0f, 0.0f);
            sphere->m_center = matrix.getTrans();
        } else {
            mm::Vec3 pos = matrix.getTrans();
            work->m_move.x = pos.x - sphere->m_center.x;
            work->m_move.y = pos.y - sphere->m_center.y;
            work->m_move.z = pos.z - sphere->m_center.z;
            float lengthSq = work->m_move.x * work->m_move.x + work->m_move.y * work->m_move.y;
            if (work->m_move.z * work->m_move.z + lengthSq >= 4.0f) work->m_move = mm::Vec3(0.0f, 0.0f, 0.0f);
            sphere->m_center = pos;
        }
        type = IDCOLI_BASE_SUB_CHARACTER;
    }
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

void IDColiPrimitive::createBaseInBox(void* base, IDColiBaseType& type, const mm::Mat44& matrix, const mm::Vec3& size) {
    CLBoxWork* box = static_cast<CLBoxWork*>(base);
    calcBaseBoxSetup(box, matrix, size);
    type = IDCOLI_BASE_IN_BOX;
    box->m_max.x += 4.0f;
    box->m_min.x -= 4.0f;
    box->m_max.y += 4.0f;
    box->m_min.y -= 4.0f;
    box->m_max.z += 4.0f;
    box->m_min.z -= 4.0f;
}

void IDColiPrimitive::createBaseCharacter(void* base, IDColiBaseType& type, const mm::Mat44& matrix,
                                          const mm::Vec3& size) {
    mm::Vec3 axis(matrix.m[0][0] + matrix.m[1][0] + matrix.m[2][0], matrix.m[0][1] + matrix.m[1][1] + matrix.m[2][1],
                  matrix.m[0][2] + matrix.m[1][2] + matrix.m[2][2]);
    float scale = axis.length() * IDColiObj::OBJ_CALC_RADIUS;
    float radius = size.x * scale;
    float length = scale * size.y + radius * -2.0f;
    if (length <= 0.01f) {
        CLSphereWork* sphere = static_cast<CLSphereWork*>(base);
        sphere->m_radius = radius;
        sphere->m_center = matrix.getTrans();
        sphere->m_center.y += radius;
        type = IDCOLI_BASE_SUB_CHARACTER;
    } else {
        CLCapsuleWork* capsule = static_cast<CLCapsuleWork*>(base);
        capsule->m_radius = radius;
        capsule->m_pos = matrix.getTrans();
        capsule->m_pos.y += radius;
        capsule->m_end = capsule->m_pos;
        capsule->m_end.y += length;
        calcCapsuleSetup(capsule);
        type = IDCOLI_BASE_CHARACTER;
    }
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

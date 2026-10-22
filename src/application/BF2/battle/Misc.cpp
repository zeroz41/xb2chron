#include "btl/Misc.h"
#include "mm/Math.h"

namespace btl {
namespace Misc {

void Normalize(mm::Vec3& v) {
    float length = v.length();
    if (length > 1e-6f) {
        float scale = 1.0f / length;
        v.x = scale * v.x;
        v.y = scale * v.y;
        v.z = scale * v.z;
    } else if (length == 0.0f) {
        v = mm::Vec3::unitZ;
    } else {
        v.x = v.x * 1e6f;
        v.y = v.y * 1e6f;
        v.z = v.z * 1e6f;
        length = v.length();
        if (length <= 1e-6f) {
            v = mm::Vec3::zero;
        } else {
            float scale = 1.0f / length;
            v.x = scale * v.x;
            v.y = scale * v.y;
            v.z = scale * v.z;
        }
    }
}

bool CalcDirection(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3& out) {
    mm::Vec3 dir = to - from;
    if (dir.length() <= 1e-6f) {
        out = mm::Vec3::zero;
        return false;
    }
    Normalize(dir);
    out = dir;
    return true;
}

void GetCrossDirection(const mm::Vec3& v, mm::Vec3& out, CROSS_MODE mode) {
    out = mode == CROSS_MODE_0 ? mm::Vec3(-v.z, 0.0f, v.x) : mm::Vec3(v.z, 0.0f, -v.x);
}

void GetPostureDirection(const mm::Quat& q, mm::Vec3& out) {
    const mm::Vec3& v = mm::Vec3::unitZ;
    float tx = (q.y * v.z - q.z * v.y) + q.w * v.x;
    float ty = (q.z * v.x - q.x * v.z) + q.w * v.y;
    float tz = (q.x * v.y - q.y * v.x) + q.w * v.z;
    float tw = -q.x * v.x - q.y * v.y - q.z * v.z;
    out.x = (-(q.z * ty) + q.y * tz - q.x * tw) + q.w * tx;
    out.y = (-(q.x * tz) + q.z * tx - q.y * tw) + q.w * ty;
    out.z = (-(q.y * tx) + q.x * ty - q.z * tw) + q.w * tz;
}

float CalcAngle(const mm::Vec3& a, const mm::Vec3& b, bool isSigned) {
    mm::Vec3 dirA = a;
    mm::Vec3 dirB = b;
    if (!(mm::fabs(dirA.length() - 1.0f) <= 1e-6f)) {
        Normalize(dirA);
    }
    if (!(mm::fabs(dirB.length() - 1.0f) <= 1e-6f)) {
        Normalize(dirB);
    }
    float angle = mm::acos(mm::clamp(dirA.dot(dirB), -1.0f, 1.0f));
    if (isSigned) {
        float cross = dirA.z * dirB.x - dirA.x * dirB.z;
        return cross < 0.0f ? -angle : angle;
    }
    return angle;
}

float CalcRotY(const mm::Vec3& v) {
    return CalcAngle(mm::Vec3::unitZ, v, true);
}

}  // namespace Misc
}  // namespace btl

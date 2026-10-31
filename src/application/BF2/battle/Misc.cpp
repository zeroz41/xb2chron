#include "btl/Misc.h"
#include "mm/Math.h"
#include "fw/Transform.h"
#include "gf/GfObjUtil.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "ml/MTRand.h"
#include <math.h>

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

bool NormalizeXZ(mm::Vec3& v) {
    float length = ::sqrtf(v.x * v.x + v.z * v.z);
    if (length <= 1e-6f) {
        v = mm::Vec3::unitZ;
        return false;
    }
    float scale = 1.0f / length;
    v.y = 0.0f;
    v.x = scale * v.x;
    v.z = scale * v.z;
    return true;
}

float CalcLength(const mm::Vec3& a, const mm::Vec3& b) {
    return (b - a).length();
}

float CalcSquareLength(const mm::Vec3& a, const mm::Vec3& b) {
    mm::Vec3 d = b - a;
    return d.x * d.x + d.y * d.y + d.z * d.z;
}

float CalcLengthXZ(const mm::Vec3& a, const mm::Vec3& b) {
    float dx = b.x - a.x;
    float dz = b.z - a.z;
    return ::sqrtf(dx * dx + dz * dz);
}

float CalcSquareLengthXZ(const mm::Vec3& a, const mm::Vec3& b) {
    float dx = b.x - a.x;
    float dz = b.z - a.z;
    return dx * dx + dz * dz;
}

float CalcLengthXZ(const mm::Vec3& v) {
    return ::sqrtf(v.x * v.x + v.z * v.z);
}

bool CalcDirectionXZ(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3& out) {
    out.x = to.x - from.x;
    out.z = to.z - from.z;
    return NormalizeXZ(out);
}

void RandomVector(mm::Vec3& out) {
    out.x = 0.5f - ml::mtRandf1();
    out.y = 0.5f - ml::mtRandf1();
    out.z = 0.5f - ml::mtRandf1();
    Normalize(out);
}

void RandomVectorXZ(mm::Vec3& out) {
    out.x = 0.5f - ml::mtRandf1();
    out.z = 0.5f - ml::mtRandf1();
    NormalizeXZ(out);
}

bool GetObjectTransform(gf::GF_OBJ_HANDLE* handle, mm::Vec3& out, TRANS_TYPE type) {
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    return GetObjectTransform(gf::GfObjUtil::getObj(handle), out, type);
}

bool GetNodePosition(gf::GF_OBJ_HANDLE* handle, const char* node, mm::Vec3& out) {
    gf::GfObj* obj = gf::GfObjUtil::getObj(handle);
    if (obj == nullptr) {
        return false;
    }
    gf::GfObjAcc acc(obj);
    int bone = acc.getBoneIdx(node);
    if (bone < 0) {
        return false;
    }
    fw::Transform transform;
    acc.getBoneTransform(transform, bone);
    out = transform.position;
    return true;
}

// the trust stage's bounds: its row's KizunaMin and KizunaMax in BDAT file 51 (the trust stages' table)
void GetKizunaMinMax(int stage, int& min, int& max) {
    int id = CovertKizunaStageToID(stage);
    unsigned char* fp = gf::GfDataBdat::getFP(51);
    min = static_cast<unsigned short>(Bdat::getValCheck(fp, "KizunaMin", id, 2));
    max = static_cast<unsigned short>(Bdat::getValCheck(fp, "KizunaMax", id, 2));
}

int CovertKizunaStageToID(int stage) {
    return 7 - stage;
}

bool CheckInRange(const mm::Vec3& a, const mm::Vec3& b, float range, bool xz) {
    float length = xz ? CalcLengthXZ(a, b) : (a - b).length();
    return length <= range;
}

}  // namespace Misc
}  // namespace btl

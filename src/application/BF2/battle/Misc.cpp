#include "btl/Misc.h"
#include "mm/Math.h"
#include "fw/Transform.h"
#include "gf/GfObjUtil.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "ml/MTRand.h"
#include "fw/ColiCheck.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComModel.h"
#include "classes/fw/ModelObject.h"
#include "classes/gf/SCOM_OBJ_VFADE.h"
#include "ml/ScnObjAccVolumeFade.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/gf/GfGameParty.h"
#include "btl/Utility.h"
#include <float.h>
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

unsigned int GetFlagBitNum(unsigned int bits) {
    bits = bits - ((bits >> 1) & 0x55555555);
    bits = (bits & 0x33333333) + ((bits >> 2) & 0x33333333);
    bits = (bits + (bits >> 4)) & 0x0F0F0F0F;
    bits = bits + (bits >> 8);
    bits = bits + (bits >> 16);
    return bits & 0x3F;
}

bool GetObjectTransform(gf::GF_OBJ_HANDLE* handle, mm::Vec3& out, TRANS_TYPE type) {
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    return GetObjectTransform(gf::GfObjUtil::getObj(handle), out, type);
}

bool GetObjectTransform(const gf::GfObj* obj, mm::Vec3& out, TRANS_TYPE type) {
    if (obj == nullptr) {
        return false;
    }
    gf::GfObjAcc acc(const_cast<gf::GfObj*>(obj));
    const fw::Transform& transform = acc.getWorldTransform();
    switch (type) {
    case TRANS_TYPE_POS:
        out = transform.position;
        break;
    case TRANS_TYPE_DIR:
        GetPostureDirection(transform.rotation, out);
        break;
    default:
        return false;
    }
    return true;
}

bool GetObjectDirection(gf::GF_OBJ_HANDLE* handle, mm::Vec3& out, bool xz) {
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    if (!GetObjectTransform(gf::GfObjUtil::getObj(handle), out, TRANS_TYPE_DIR)) {
        return false;
    }
    if (xz) {
        NormalizeXZ(out);
    }
    return true;
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

void SetVolumeFadeRate(gf::GF_OBJ_HANDLE* handle, float rate, unsigned int value, int parts) {
    if (parts < 0) {
        parts = -1;
    }
    gf::SCOM_OBJ_VFADE::createBattleParts(handle, 0.0f, rate, value, static_cast<gf::VFPARTS>(parts));
    float alpha = parts == -1 && rate <= 0.0f ? 0.0f : 1.0f;
    gf::GfObjAcc acc(handle);
    acc.setAlphaNormal(alpha);
}

float GetVolumeFadeAlphaRate(gf::GF_OBJ_HANDLE* handle) {
    float rate = 0.0f;
    if (gf::GfObj* obj = gf::GfObjUtil::getObj(handle)) {
        if (gf::GfComModel* model = obj->getComponent<gf::GfComModel>(1)) {
            if (model->m_model != nullptr) {
                ml::ScnObjAccVolumeFade fade(model->m_model->getInterface());
                rate = 1.0f - fade.getRatio(0);
            }
        }
    }
    return rate;
}

int GetPartyID(gf::GF_OBJ_HANDLE* handle) {
    if (!Utility::IsThirdCharacter(handle)) {
        return gf::GfGameParty::getPartyId(handle);
    }
    for (unsigned int i = 0; i < 3; i++) {
        gf::GF_OBJ_HANDLE* driver = gf::GfGameParty::getHandleDriver(i, static_cast<gf::PTPOS>(0));
        if (driver == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            continue;
        }
        gf::GfObjAcc acc(driver);
        if (acc.getBdatId() == 1) {
            return i;
        }
    }
    return -1;
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

int GetKizunaStage(int kizuna, float* ratio) {
    for (int stage = 0; stage < 6; stage++) {
        int min;
        int max;
        GetKizunaMinMax(stage, min, max);
        if (kizuna >= min && kizuna <= max) {
            if (ratio != nullptr) {
                if (kizuna <= min) {
                    *ratio = 0.0f;
                } else if (kizuna >= max) {
                    *ratio = 1.0f;
                } else {
                    float range = static_cast<float>(max - min);
                    *ratio = static_cast<float>(kizuna - min) / range;
                }
            }
            return stage;
        }
    }
    if (ratio != nullptr) {
        *ratio = 1.0f;
    }
    return 6;
}

float GetLandHeight(const mm::Vec3& pos, float offset, bool water, bool valid) {
    mm::Vec3 from = pos;
    from.y += offset;
    mm::Vec3 out;
    bool found;
    if (water) {
        found = GetWaterHeight(out, from, offset + 15.0f);
    } else if (valid) {
        found = GetValidLandHeight(out, from, offset + 15.0f);
    } else {
        float range = offset + 5.0f;
        if (fw::ColiCheck::getSnapPos(out, from, range, 0x80000060)) {
            found = true;
        } else {
            from.y -= range;
            found = fw::ColiCheck::getSnapPos(out, from, 10.0f, 0x80000060);
        }
    }
    return found ? out.y : pos.y - 3000.0f;
}

bool GetWaterHeight(mm::Vec3& out, mm::Vec3& from, float range) {
    fw::ColiCheckConfig config;
    config.m_mode = 2;
    config.m_option = false;
    config.m_flags = 9;
    config.m_mask = 0x43;
    mm::Vec3 to(from.x, from.y - range, from.z);
    fw::TColiCheckResult<256> result;
    fw::ColiCheck::testLine(result, from, to, config);
    if (result.getHitNum() != 0) {
        const fw::ContactInfo* nearest = nullptr;
        float minDist = FLT_MAX;
        for (auto it = result.m_hits.begin(); it != result.m_hits.end(); ++it) {
            if (it->m_material->m_attribute & 3) {
                float dist = CalcSquareLength(from, it->m_position);
                if (dist < minDist) {
                    minDist = dist;
                    nearest = &*it;
                }
            }
        }
        if (nearest != nullptr) {
            out = nearest->m_position;
            return true;
        }
    }
    out = from;
    return false;
}

bool GetValidLandHeight(mm::Vec3& out, mm::Vec3& from, float range) {
    fw::ColiCheckConfig config;
    config.m_mode = 2;
    config.m_option = false;
    config.m_flags = 9;
    config.m_mask = 0x80000040;
    mm::Vec3 to(from.x, from.y - range, from.z);
    fw::TColiCheckResult<256> result;
    fw::ColiCheck::testLine(result, from, to, config);
    if (result.getHitNum() != 0) {
        const fw::ContactInfo* nearest = nullptr;
        float minDist = FLT_MAX;
        for (auto it = result.m_hits.begin(); it != result.m_hits.end(); ++it) {
            if ((it->m_material->m_attribute & 0xB3) == 0) {
                float dist = CalcSquareLength(from, it->m_position);
                if (dist < minDist) {
                    minDist = dist;
                    nearest = &*it;
                }
            }
        }
        if (nearest != nullptr) {
            out = nearest->m_position;
            return true;
        }
    }
    out = from;
    return false;
}

bool CheckInRange(const mm::Vec3& pos, BattleCharacter* chr, float range, bool xz) {
    if (chr == nullptr) {
        return false;
    }
    if (const CharacterParameter* param = chr->GetCharacterParameterConst(true)) {
        range += param->m_radius;
    }
    return CheckInRange(pos, chr->m_pos, range, xz);
}

bool CheckInRange(const mm::Vec3& a, const mm::Vec3& b, float range, bool xz) {
    float length = xz ? CalcLengthXZ(a, b) : (a - b).length();
    return length <= range;
}

bool CheckInRange(const mm::Vec3& pos, gf::GF_OBJ_HANDLE* handle, float range, bool xz) {
    gf::GfObj* obj;
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) || (obj = gf::GfObjUtil::getObj(handle)) == nullptr) {
        return false;
    }
    gf::GfObjAcc acc(obj);
    mm::Vec3 objPos = acc.getWorldTransform().position;
    if (const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle)) {
        if (const CharacterParameter* param = chr->GetCharacterParameterConst(true)) {
            range += param->m_radius;
        }
    }
    return CheckInRange(pos, objPos, range, xz);
}

}  // namespace Misc
}  // namespace btl

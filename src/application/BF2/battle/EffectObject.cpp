#include "btl/EffectObject.h"
#include <algorithm>
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/EffectPack.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComTransform.h"
#include "gf/GfObjUtil.h"
#include "plugin/Bdat.h"
#include "btl/Misc.h"
#include "btl/Utility.h"
#include "ml/MTRand.h"
#include "classes/btl/EffectManager.h"

namespace btl {

EffectObject::EffectObject() : m_object(nullptr), m_circleParamA(0), m_id(0), m_kind(KIND_NONE) {
    Initialize(0);
}

void EffectObject::SetOneShotHitData(float rate, bool flag) {
    m_oneShotHit.m_rate = rate;
    m_oneShotHit.m_isActive = true;
    m_oneShotHit.m_flag = flag;
    m_oneShotHit.m_isFirst = true;
    m_oneShotHit.m_noAddAttack = m_addAtkNum == 0;
    m_hitKind = HIT_KIND_ONE_SHOT;
}

void EffectObject::SetObject(gf::GF_OBJ_HANDLE* handle, mm::mtl::FixedVector<fw::EffectPack*, 8>& packs) {
    gf::GfObj* obj = gf::GfObjUtil::getObj(handle);
    if (obj == nullptr) {
        return;
    }
    gf::GfComTransform* transform = obj->getComponent<gf::GfComTransform>(0);
    if (transform == nullptr) {
        return;
    }
    m_kind = KIND_OBJECT;
    m_object = handle;
    m_effectPacks = packs;
    m_pos = transform->getPosition();
    m_isTimed = false;
}

void EffectObject::SetArtsData(int slot, int artsKind, bool flag, unsigned int artsParam) {
    const BattleCharacter* chara = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(m_owner);
    if (chara != nullptr) {
        SetArtsData(*chara->GetArtsSlotData(slot, !flag, -1), artsKind, artsParam);
    }
}

void EffectObject::SetArtsData(const ARTS_SLOT_DATA& slot, int artsKind, unsigned int artsParam) {
    m_artsSlot = slot;
    m_artsParam = artsParam;
    m_artsKind = artsKind;
}

void EffectObject::SetBulletData(int bulletId, int param) {
    m_bulletId = bulletId;
    m_bulletParam = param;
    m_addAtkNum = Bdat::getValCheckU8(gf::GfDataBdat::getFP(18), "AddAtkNum", bulletId);
    if (m_hitKind == HIT_KIND_ONE_SHOT) {
        m_oneShotHit.m_noAddAttack = m_addAtkNum == 0;
    }
}

void EffectObject::SetIntervalHitData(float interval, float rate, bool flag0, float count, float maxHit, bool flag1,
                                      bool flag2, bool flag3) {
    m_intervalHit.m_rate = rate;
    m_intervalHit.m_interval = interval * 100.0f;
    m_intervalHit.m_maxHit = maxHit;
    m_intervalHit.m_count = count;
    m_intervalHit.m_flag0 = flag0;
    m_intervalHit.m_flag1 = flag1;
    m_intervalHit.m_flag2 = flag2;
    m_intervalHit.m_flag3 = flag3;
    memset(m_intervalHit.m_hitFlags, 0, sizeof(m_intervalHit.m_hitFlags));
    m_hitKind = HIT_KIND_INTERVAL;
    m_fadeFrames = 5;
}

void EffectObject::SetSubEffectParam(int a, int b, int c) {
    m_circleParamA = a;
    m_circleParamB = b;
    m_circleParamC = c;
}

void EffectObject::SetMoveParam(const EffectMoveComponent::MOVE_PARAM& param) {
    m_move.Initialize(param);
}

void EffectObject::SetEndEffect(const char* name) {
    m_endEffect = name;
}

bool EffectObject::IsEnd() const {
    return m_isTimed && m_remainTime <= 0.0f;
}

void EffectObject::UpdateSubEffect() {
    if (m_circleParamA != 1) {
        return;
    }
    const BattleCharacter* owner = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(m_owner);
    if (owner == nullptr) {
        return;
    }
    mm::mtl::FixedVector<unsigned char, 90> list;
    Utility::GetCharacterList(list, owner->m_handle, Utility::CHECK_CHR_NUM_MODE(1), 0x23);
    float range = m_circleParamB;
    CharacterManager* manager = mm::mtl::PtrSingleton<CharacterManager>::sys();
    std::for_each(list.begin(), list.end(), [&](unsigned char id) {
        const BattleCharacter* chara = manager->GetCharacterConst(id);
        const CharacterParameter* param = chara->GetCharacterParameterConst(true);
        if (param != nullptr && Misc::CheckInRange(m_pos, chara->m_pos, range + param->m_radius, true)) {
            mm::mtl::PtrSingleton<EffectManager>::sys()->AddCircleDamageBonus(id, m_circleParamC);
        }
    });
}

void EffectObject::StartNextAttack() {
    const BattleCharacter* chara = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(pad_58);
    mm::Vec3 target;
    if (!Misc::GetNodePosition(pad_58, chara->pad_C50, target)) {
        if (chara != nullptr) {
            target = chara->m_pos;
            target.y += chara->GetCharacterParameterConst(true)->pad_38;
        } else {
            target = m_move.m_dir * -3.5f;
            target += m_pos;
        }
    }
    mm::Vec3 dir;
    dir.x = target.x - m_pos.x;
    dir.y = target.y - m_pos.y;
    dir.z = target.z - m_pos.z;
    Misc::Normalize(dir);
    EffectMoveComponent::MOVE_PARAM param;
    param.m_accelWait = 0.0f;
    param.m_endFlags = 0;
    param.m_type = EffectMoveComponent::MOVE_TYPE_NORMAL;
    param.m_dir = dir;
    unsigned char* fp = gf::GfDataBdat::getFP(18);
    int id = m_bulletId;
    float first = Bdat::getValCheckU16(fp, "SpdFirst", id) * 0.01f;
    param.m_speed = first;
    float last = Bdat::getValCheckU16(fp, "SpdLast", id) * 0.01f;
    param.m_speedLimit = last;
    float accelStart = Bdat::getValCheckU16(fp, "AclStart", id);
    float accelFrames = Bdat::getValCheckU16(fp, "AclEnd", id) - accelStart;
    param.m_accel = accelFrames <= 0.0f ? 0.0f : (last - first) / accelFrames;
    param.m_accelWait = accelStart;
    float length = (m_pos - target).length();
    param.m_endFlags = 2;
    param.m_endParam[1].m_value = length;
    if (chara != nullptr) {
        int index = chara->m_voiceIndex;
        param.m_endFlags = 3;
        param.m_endParam[0].m_index = index;
    }
    m_move.Initialize(param);
    m_isTimed = false;
    if (m_hitKind == HIT_KIND_ONE_SHOT) {
        m_oneShotHit.m_isActive = true;
        m_oneShotHit.m_flag = true;
        m_oneShotHit.m_isFirst = true;
        m_oneShotHit.m_noAddAttack = m_addAtkNum == 0;
    }
}

void EffectObject::StartAdditionalAttack() {
    // the target: GetCrossDirection's side first, then 3.5 along the turned direction from m_pos
    mm::Vec3 target;
    mm::Vec3 launch;
    {
        mm::Vec3 dir = m_move.m_dir;
        dir.x = -dir.x;
        dir.z = -dir.z;
        if (!Misc::NormalizeXZ(dir)) {
            dir = mm::Vec3::unitZ;
        }
        Misc::GetCrossDirection(dir, target, static_cast<Misc::CROSS_MODE>(ml::mtRandf1() < 0.5f));
        // up to 50 degrees aside, then 40 to 60 degrees up
        Misc::TurnDirectionAngle(dir, target, ml::mtRandf1() * 0.87266463f, true);
        dir.y = tanf(ml::mtRandf1(0.69813168f, 1.04719758f));
        Misc::Normalize(dir);
        target = dir * 3.5f;
        target += m_pos;
        launch = dir;
    }
    Misc::NormalizeXZ(launch);
    // 78 degrees up
    launch.y = tanf(1.36135685f);
    Misc::Normalize(launch);
    EffectMoveComponent::MOVE_PARAM param;
    param.m_type = EffectMoveComponent::MOVE_TYPE_PARABOLA;
    param.m_dir = launch;
    float frames = __builtin_fmaxf(Bdat::getValCheckU8(gf::GfDataBdat::getFP(18), "AddAtkDelay", m_bulletId), 1.0f);
    float cosine = sqrtf(1.0f - launch.y * launch.y);
    float speed = Misc::CalcLengthXZ(m_pos, target) / frames / cosine;
    param.m_accel = 0.0f;
    param.m_accelWait = 0.0f;
    param.m_speed = speed;
    param.m_speedLimit = speed;
    param.m_parabola.m_start.x = m_pos.x;
    param.m_parabola.m_start.y = m_pos.y;
    param.m_parabola.m_start.z = m_pos.z;
    param.m_parabola.m_target.x = target.x;
    param.m_parabola.m_target.y = target.y;
    param.m_parabola.m_target.z = target.z;
    float length = Misc::CalcLengthXZ(m_pos, target);
    param.m_endFlags = 4;
    param.m_endParam[2].m_value = length;
    m_move.Initialize(param);
    m_isTimed = false;
    if (m_hitKind == HIT_KIND_ONE_SHOT) {
        m_oneShotHit.m_isActive = false;
        m_oneShotHit.m_flag = false;
        m_oneShotHit.m_isFirst = false;
        m_oneShotHit.m_noAddAttack = false;
    }
}

}  // namespace btl

#include "btl/EffectObject.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/EffectPack.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComTransform.h"
#include "gf/GfObjUtil.h"
#include "plugin/Bdat.h"

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

void EffectObject::fn_710009B8C4(int slot, int artsKind, bool flag, unsigned int artsParam) {
    const BattleCharacter* chara = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(m_owner);
    if (chara != nullptr) {
        fn_710009B958(*chara->GetArtsSlotData(slot, !flag, -1), artsKind, artsParam);
    }
}

void EffectObject::fn_710009B958(const ARTS_SLOT_DATA& slot, int artsKind, unsigned int artsParam) {
    m_artsSlot = slot;
    m_artsParam = artsParam;
    m_artsKind = artsKind;
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

void EffectObject::fn_710009BA78(unsigned char a, unsigned char b, unsigned short c) {
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

}  // namespace btl

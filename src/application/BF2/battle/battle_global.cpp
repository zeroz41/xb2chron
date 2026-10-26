#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/ShakeCameraManager.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/btl/UIManager.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "classes/ai/AiScriptManager.h"
#include "classes/gf/GfScriptManager.h"
#include "classes/gf/GfGameManager.h"
#include "classes/btl/TalkManager.h"
#include "classes/btl/BattleCharacter.h"
#include "btl/Misc.h"
#include "classes/fw/EffectManager.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComDynamics.h"
#include "classes/btl/ShakeCameraElementRandom.h"
#include "classes/btl/ShakeCameraElementCameraAxis.h"

namespace btl {

void BattleGlobal::PreUpdate(const fw::UpdateInfo& info) {
    sys()->PreUpdateProc(info);
}

bool BattleGlobal::IsEnableBattle() const {
    return !gf::GfGameManager::isBattleStop();
}

bool BattleGlobal::fn_71000068F8() {
    return pad_bit49 && pad_bit50;
}

void BattleGlobal::SetElementalComboImmortal(gf::GF_OBJ_HANDLE* handle) {
    m_elementalComboImmortal = handle;
}

void BattleGlobal::Update(const fw::UpdateInfo& info) {
    sys()->UpdateProc(info);
}

void BattleGlobal::PostUpdate(const fw::UpdateInfo& info) {
    sys()->PostUpdateProc(info);
}

bool BattleGlobal::fn_710000A6CC() {
    return pad_bit49;
}

void BattleGlobal::UpdateAttackData(unsigned int id) {
    findAttackData(id);
}

int BattleGlobal::GetAttackDamage(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->damage;
    }
    return -1;
}

void BattleGlobal::SetAttackAttr(unsigned int id, int attr) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->attr = attr;
    }
}

int BattleGlobal::GetAttackAttr(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr && data->attr != 9) {
        return data->attr;
    }
    return -1;
}

void BattleGlobal::SetEndDropHealPot2(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->endDropHealPot2 = true;
    }
}

bool BattleGlobal::IsEndDropHealPot2(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->endDropHealPot2;
    }
    return false;
}

void BattleGlobal::fn_710000B338(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->endCriticalRecastEnhance = true;
    }
}

bool BattleGlobal::IsEndCriticalRecastEnhance(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->endCriticalRecastEnhance;
    }
    return false;
}

void BattleGlobal::SetJustDistanceAttack(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->justDistanceAttack = true;
    }
}

bool BattleGlobal::IsJustDistanceAttack(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->justDistanceAttack;
    }
    return false;
}

void BattleGlobal::fn_710000B4D0(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->pad_bit11 = true;
    }
}

bool BattleGlobal::fn_710000B52C(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->pad_bit11;
    }
    return false;
}

void BattleGlobal::SetCriticalRecastEnhanceEnd(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->criticalRecastEnhanceEnd = true;
    }
}

bool BattleGlobal::fn_710000B5F4(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->criticalRecastEnhanceEnd;
    }
    return false;
}

void BattleGlobal::fn_710000B664(unsigned int id, bool on) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->pad_bit10 = on;
    }
}

bool BattleGlobal::fn_710000B6C0(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->pad_bit10;
    }
    return false;
}

void BattleGlobal::SetEnableAddElementalBall(unsigned int id, bool enable) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->enableAddElementalBall = enable;
    }
}

bool BattleGlobal::IsEnableAddElementalBall(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->enableAddElementalBall;
    }
    return true;
}

void BattleGlobal::SetResistantBreakDamageEnd(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->resistantBreakDamageEnd = true;
    }
}

bool BattleGlobal::IsEnableResistantBreakDamage(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    return data != nullptr && !data->resistantBreakDamageEnd;
}

bool BattleGlobal::fn_710000B8CC(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->chainAttack;
    }
    return false;
}

void BattleGlobal::SetPermitArts(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->permitArts = true;
    }
}

bool BattleGlobal::IsPermitArts(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->permitArts;
    }
    return false;
}

void BattleGlobal::fn_710000BA08(unsigned int id, bool on) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->pad_bit8 = false;
        if (on) {
            data->pad_bit9 = true;
        } else {
            data->pad_bit9 = false;
        }
    }
}

int BattleGlobal::fn_710000BA74(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        if (data->pad_bit8) {
            return 1;
        }
        if (data->pad_bit9) {
            return 2;
        }
    }
    return 0;
}

void BattleGlobal::SetShootBullet(unsigned int id, bool shoot) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->noShootBullet = !shoot;
    }
}

bool BattleGlobal::IsShootBullet(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    return data == nullptr || !data->noShootBullet;
}

void BattleGlobal::SetValidAttackRange(unsigned int id, bool valid) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->validAttackRange = valid;
    }
}

bool BattleGlobal::IsValidAttackRange(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->validAttackRange;
    }
    return true;
}

void BattleGlobal::AddDamageRate(unsigned int id, float rate, bool markChanged) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->damageRate = (static_cast<float>(data->damageRate) / 65536.0f + rate) * 65536.0f;
        if (markChanged) {
            data->damageRateChanged = true;
        }
    }
}

void BattleGlobal::MulDamageRate(unsigned int id, float rate, bool markChanged) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->damageRate = static_cast<float>(data->damageRate) / 65536.0f * rate * 65536.0f;
        if (markChanged) {
            data->damageRateChanged = true;
        }
    }
}

float BattleGlobal::GetDamageRate(unsigned int id, bool* changed) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        if (changed != nullptr) {
            *changed = data->damageRateChanged;
        }
        return static_cast<float>(data->damageRate) / 65536.0f;
    }
    if (changed != nullptr) {
        *changed = false;
    }
    return 1.0f;
}

// ---- session 19 ----

const BattleGlobal::ELEMENTAL_COMBO_FLOW_DATA& BattleGlobal::GetElementalComboFlowData(int id) const {
    return m_elementalComboFlow[static_cast<unsigned int>(id) < 66 ? id : 0];
}

int BattleGlobal::GetElementalComboStage(int id) const {
    return GetElementalComboFlowData(id).stage;
}

int BattleGlobal::GetFirstStageElementalComboData(int id) const {
    while (id != 0) {
        const ELEMENTAL_COMBO_FLOW_DATA& data = GetElementalComboFlowData(id);
        if (data.stage == 1) {
            return id;
        }
        id = data.prevId;
    }
    return id;
}

int BattleGlobal::GetNormalAttackArtsID(int chara, int weapon, int step) const {
    unsigned short id = m_normalAttackArtsID[chara][weapon][step];
    if (id == 0) {
        id = m_normalAttackArtsID[0][weapon][step];
    }
    return id;
}

unsigned short BattleGlobal::fn_71000053C4(int id) const {
    return pad_8374[static_cast<int>(id - 17u)];
}

const BattleGlobal::ELEMENTAL_COMBO_FLOW_DATA& BattleGlobal::fn_71000053F8(int id) const {
    return m_elementalComboFlow[id];
}

bool BattleGlobal::fn_7100007554() const {
    return pad_5d54 != 0;
}

bool BattleGlobal::IsGameOver() const {
    if (m_gameOver) {
        return true;
    }
    return gf::GfGameManager::isPlayerDeadSequence();
}

void BattleGlobal::fn_710000903C() {
    pad_83b2 = 0;
    pad_83b4 = 0xFF;
}

bool BattleGlobal::fn_710000A7FC(int index) const {
    return (pad_83b8[index >> 3] & (1 << (index & 7))) != 0;
}

void BattleGlobal::fn_710000AC7C(int index) {
    int byte = index >> 3;
    int bit = index & 7;
    pad_83b8[byte] &= ~(1 << bit);
}

void BattleGlobal::fn_710000ACA4(int index) {
    int byte = index >> 3;
    int bit = index & 7;
    pad_83bc[byte] |= 1 << bit;
}

void BattleGlobal::RequestJingle(JINGLE_TYPE type) {
    m_jingleRequest = type;
}

bool BattleGlobal::IsJinglePlaying() const {
    return m_jingleHandle != -1;
}

void BattleGlobal::PlayErrorSE() {
    if (!m_errorSePlayed) {
        gf::GfMenuObjUtil::playSECommon(2);
        m_errorSePlayed = true;
    }
}

bool BattleGlobal::fn_710000C440(int index) {
    int byte = index >> 3;
    int mask = 1 << (index & 7);
    unsigned char& flags = pad_83bf[byte];
    if (flags & mask) {
        return false;
    }
    flags |= mask;
    return true;
}

bool BattleGlobal::fn_710000C610() const {
    return pad_5d60 <= 0.0f;
}

bool BattleGlobal::fn_710000C624(gf::GF_OBJ_HANDLE* handle) const {
    if (pad_5d54 == 0) {
        return false;
    }
    return pad_5d48 == handle;
}

bool BattleGlobal::fn_710000C648() const {
    return static_cast<unsigned int>(pad_5d54 - 3) < 5;
}

void BattleGlobal::fn_710000C660(ARTS_DATA& data) const {
    DataManager::sys()->GetArtsData(static_cast<ARTS_DATA::DATA_TYPE>(pad_5d68 & 7), pad_5d68 >> 3, data);
}

bool BattleGlobal::fn_710000CEF4() const {
    return pad_bit18;
}

bool BattleGlobal::fn_710000CF04() const {
    return pad_bit21;
}

void BattleGlobal::fn_710000DE04(bool side, int add) {
    unsigned char& count = pad_83c0[!side];
    int value = count + add;
    count = value < 0 ? 0 : (value > 0xFF ? 0xFF : value);
}

bool BattleGlobal::fn_710000DE34(bool side) {
    unsigned char& count = pad_83c0[!side];
    if (count == 0) {
        return false;
    }
    count += 0xFF;
    return true;
}

void BattleGlobal::ApplyBattleCameraAdjustment(mm::Vec3& pos, mm::Vec3& target) {
    if (m_shakeCamera != nullptr) {
        m_shakeCamera->ApplyShake(pos, target);
    }
}

void BattleGlobal::Create() {
#line 330
    BattleGlobal* global = new (gf::getAllocator(gf::ALLOCATOR(1)), __FILE__, __LINE__, 8) BattleGlobal;
    global->Initialize();
}

bool BattleGlobal::IsSlowProc(unsigned int id) const {
    return GetSlowProcDataConst(id) != nullptr;
}

void BattleGlobal::fn_710000A6DC() {
    if (pad_bit49) {
        pad_bit50 = !pad_bit50;
    }
}

bool BattleGlobal::fn_710000A724() {
    return (pad_bit49 && pad_bit50) || pad_bit35;
}

void BattleGlobal::fn_710000A764() {
    pad_bit40 = false;
    pad_bit41 = false;
}

void BattleGlobal::NotifyShiftTimeOver() {
    if (UIManager::sys()->pad_bit15) {
        pad_bit41 = true;
    }
}

bool BattleGlobal::fn_710000DA48() const {
    if (m_challengeAnySuccess) {
        return false;
    }
    return pad_5d9c != 0;
}

void BattleGlobal::fn_710000DA8C() {
    if (m_challengeAnySuccess) {
        return;
    }
    if (pad_5d9c != 0 && pad_5d9c < 3) {
        pad_5d9c = 3;
    }
}

bool BattleGlobal::fn_710000DAD8() const {
    if (m_challengeAnySuccess) {
        return false;
    }
    return pad_5d9c > 2;
}

void BattleGlobal::fn_710000DD4C(int index, unsigned int add) {
    if (m_challengeAnySuccess) {
        return;
    }
    if (pad_5d9c != 0 && index >= 0 && index < 3) {
        unsigned int value = pad_5d78[index] + add;
        pad_5d78[index] = value < 99999999 ? value : 99999999;
    }
}

bool BattleGlobal::fn_710000DDB0(bool check) const {
    if (pad_bit22) {
        return true;
    }
    if (check && pad_5dc0 >= 0.0f) {
        return true;
    }
    return false;
}

void BattleGlobal::fn_71000063EC() {
    m_leaderHandle = m_controlHandle = gf::GfGameManager::getPartyLeaderDriver();
    if (ChainAttackManager::sys()->IsProc(false)) {
        int group = ChainAttackManager::sys()->GetGroupIndex();
        if (group >= 0) {
            m_controlHandle = gf::GfGameParty::getHandleDriver(group, 0);
        }
    }
}

bool BattleGlobal::fn_710000D468(bool check) const {
    if (pad_bit16) {
        return true;
    }
    if (check && pad_5db8 >= 0.0f) {
        return true;
    }
    return false;
}

bool BattleGlobal::fn_710000D4BC(bool check) const {
    if (pad_bit20) {
        return true;
    }
    if (check && pad_5dbc >= 0.0f) {
        return true;
    }
    return false;
}

void BattleGlobal::Destroy() {
    BattleGlobal* global = sys();
    if (global->m_shakeCamera != nullptr) {
        delete global->m_shakeCamera;
        global->m_shakeCamera = nullptr;
    }
    if (global != nullptr) {
        delete global;
    }
}

void ARTS_SLOT_DATA::GetArtsData(ARTS_DATA& data) const {
    DataManager::sys()->GetArtsData(static_cast<ARTS_DATA::DATA_TYPE>(m_dataType), m_artsID, data);
}

void ARTS_PALETTE_DATA::ResetAllRecast() {
    for (int i = 0; i < 19; i++) {
        if (m_slots[i].m_artsID != 0) {
            m_slots[i].m_recast = 0.0f;
        }
    }
    if (m_talentSlot.m_artsID != 0) {
        m_talentSlot.m_recast = 0.0f;
    }
    for (int i = 0; i < 3; i++) {
        if (m_supportSlots[i].m_artsID != 0) {
            m_supportSlots[i].m_recast = 0.0f;
        }
    }
}

const ARTS_SLOT_DATA* ARTS_PALETTE_DATA::GetSlotDataConst(int slot, bool alternate) const {
    if (slot == 15) {
        return &m_talentSlot;
    }
    return &m_slots[alternate ? slot + 16 : slot];
}

const ARTS_SLOT_DATA* ARTS_PALETTE_DATA::GetSupportSlotDataConst(int slot) const {
    return &m_supportSlots[slot];
}

bool BattleGlobal::fn_7100009618(unsigned int id) {
    bool taken = false;
    if (id != 0) {
        unsigned char priority = static_cast<unsigned char>(
            Bdat::getValCheck(gf::GfDataBdat::getFP(0xB1), "Priority", id, 1));
        if (priority > pad_83b4 || pad_83b4 == 0xFF) {
            pad_83b2 = id;
            pad_83b4 = priority;
            taken = true;
        }
    }
    return taken;
}

gf::GF_OBJ_HANDLE* BattleGlobal::GetAttackMainTargetHandle(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data == nullptr) {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    return CharacterManager::sys()->GetCharacterHandle(data->charaIndex);
}


void BattleGlobal::AddChainCount(bool narrate) {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71009B5A0F)
    static const unsigned char s_chainNarrationCount[] = {25, 50, 100};
    if (m_chainCount.count != 0xFFFFFFF) {
        m_chainCount.count++;
    }
    if (narrate) {
        unsigned int level = m_chainCount.level;
        if (level <= 2 && m_chainCount.count >= s_chainNarrationCount[level]) {
            TalkManager::sys()->PlayNarrationVoice(static_cast<TalkManager::NARRATION_TYPE>(4), level + 5, 0);
            m_chainCount.level = level + 1;
        }
    }
}

void BattleGlobal::NotifyLinkJoinBattle(gf::GF_OBJ_HANDLE* handle) {
    const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr == nullptr) {
        return;
    }
    const CharacterParameter* param = chr->GetCharacterParameterConst(true);
    if (param == nullptr || param->fn_7100085314(true)) {
        return;
    }
    int level = param->GetLevel();
    if (param->IsNamed()) {
        level += 15;
    }
    if (level > m_linkJoinLevel) {
        m_linkJoinLevel = level;
    }
    if (m_linkJoinEnemy.size() < 8) {
        LinkJoinEnemy enemy;
        enemy.handle = handle;
        enemy.time = 30.0f;
        m_linkJoinEnemy.push_back(enemy);
    }
}

gf::GF_OBJ_HANDLE* BattleGlobal::GetLinkJoinEnemyHandle(const mm::Vec3& pos) {
    gf::GF_OBJ_HANDLE* result = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    float nearest = 3.40282347e+38f;
    for (LinkJoinEnemy& enemy : m_linkJoinEnemy) {
        mm::Vec3 enemyPos;
        if (Misc::GetObjectTransform(enemy.handle, enemyPos, Misc::TRANS_TYPE_POS)) {
            float length = Misc::CalcSquareLength(enemyPos, pos);
            if (length < nearest) {
                result = enemy.handle;
                nearest = length;
            }
        }
    }
    return result;
}


BattleGlobal::~BattleGlobal() {}

void BattleGlobal::ShakeCameraRandom(const SHAKE_CAMERA_RANDOM_PARAM& param) {
    if (m_shakeCamera == nullptr) {
        return;
    }
#line 6430
    ShakeCameraElementRandom* element = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) ShakeCameraElementRandom;
    if (element == nullptr) {
        return;
    }
    int type = param.type;
    float amplitude = param.amplitude;
    float interval = param.interval;
    bool useFrameTime = param.useFrameTime;
    element->m_type = type;
    element->m_amplitude = amplitude;
    element->m_interval = fmaxf(interval, 1.0f / 30.0f);
    element->m_useFrameTime = useFrameTime;
    float fadeInTime = param.fadeInTime;
    float duration = param.duration;
    float fadeOutTime = param.fadeOutTime;
    bool vertical = param.vertical;
    element->m_fadeInTime = fadeInTime;
    element->m_duration = duration;
    element->m_fadeOutTime = fadeOutTime;
    element->m_vertical = vertical;
    m_shakeCamera->RegisterData(element);
}

void BattleGlobal::ShakeCameraAxis(const SHAKE_CAMERA_AXIS_PARAM& param) {
    if (m_shakeCamera == nullptr) {
        return;
    }
    ShakeCameraElement* element;
    if (param.axisType == 0) {
#line 6456
        ShakeCameraElementAxis* axis = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) ShakeCameraElementAxis;
        if (axis == nullptr) {
            return;
        }
        int stepCount = param.stepCount;
        int repeat = param.repeat;
        bool flag = param.flag;
        axis->m_axis = param.axis;
        axis->m_stepCount = stepCount;
        axis->m_repeat = repeat;
        axis->m_flag = flag;
        element = axis;
    } else {
        ShakeCameraElementCameraAxis::SHAKE_AXIS cameraAxis;
        switch (param.axisType) {
        case 1:
            cameraAxis = ShakeCameraElementCameraAxis::SHAKE_AXIS_X;
            break;
        case 2:
            cameraAxis = ShakeCameraElementCameraAxis::SHAKE_AXIS_NEG_X;
            break;
        case 3:
            cameraAxis = ShakeCameraElementCameraAxis::SHAKE_AXIS_Y;
            break;
        case 4:
            cameraAxis = ShakeCameraElementCameraAxis::SHAKE_AXIS_NEG_Y;
            break;
        case 5:
            cameraAxis = ShakeCameraElementCameraAxis::SHAKE_AXIS_NEG_Z;
            break;
        case 6:
            cameraAxis = ShakeCameraElementCameraAxis::SHAKE_AXIS_Z;
            break;
        default:
            return;
        }
#line 6476
        ShakeCameraElementCameraAxis* axis = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) ShakeCameraElementCameraAxis();
        if (axis == nullptr) {
            return;
        }
        axis->SetData(cameraAxis, param.stepCount, param.repeat, param.flag);
        element = axis;
    }
    int type = param.type;
    float amplitude = param.amplitude;
    float interval = param.interval;
    bool useFrameTime = param.useFrameTime;
    element->m_type = type;
    element->m_amplitude = amplitude;
    element->m_interval = fmaxf(interval, 1.0f / 30.0f);
    element->m_useFrameTime = useFrameTime;
    m_shakeCamera->RegisterData(element);
}

void BattleGlobal::SetSlowDynamicsSpeed(unsigned int id, int chara, unsigned int speed) {
    SLOW_PROC_DATA* data = GetSlowProcData(id);
    if (data == nullptr) {
        return;
    }
    const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(chara);
    if (chr == nullptr) {
        return;
    }
    gf::GfComDynamics* dynamics = chr->GetObject()->getComponent<gf::GfComDynamics>(8);
    if (dynamics == nullptr) {
        return;
    }
    dynamics->m_updater.m_timeScale = speed * 0.01f;
    data->dynamicsChara = chara;
    data->dynamicsSpeed = speed;
}

void BattleGlobal::DeleteDelayElementalComboSlow(float delay) {
    SLOW_PROC_DATA* data = GetSlowProcData(m_elementalComboSlowId);
    if (data != nullptr) {
        data->deleteDelay = delay;
        data->pad_8 = 0;
    }
}

void BattleGlobal::DeleteElementalComboSlow() {
    DeleteSlow(m_elementalComboSlowId);
    m_elementalComboSlowId = 0;
    for (int i = 0; i < 2; i++) {
        if (m_elementalComboSlowEffect[i] != 0) {
            if (m_elementalComboSlowCaster[i] != nullptr) {
                m_elementalComboSlowCaster[i]->setSpeed(m_elementalComboSlowEffect[i], 1.0f);
            } else if (fw::EffectManager::sys() != nullptr) {
                fw::EffectManager::sys()->setSpeed(m_elementalComboSlowEffect[i], 1.0f);
            }
            m_elementalComboSlowCaster[i] = nullptr;
            m_elementalComboSlowEffect[i] = 0;
        }
    }
}
}  // namespace btl

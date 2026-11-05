#include "btl/siren_battle_manager.h"
#include "btl/Utility.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/SpAttackManager.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/TalkManager.h"
#include "classes/fw/Camera.h"
#include "classes/fw/CameraManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfMenuManager.h"
#include "gf/GfGameUtil.h"
#include "mm/Mat44.h"
#include "mm/Math.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "ml/MTRand.h"
#include "plugin/Bdat.h"
#include <string.h>

namespace btl {

SirenBattleManager::~SirenBattleManager() {}

void SirenBattleManager::Create() {
#line 81
    SirenBattleManager* manager = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) SirenBattleManager;
    manager->Initialize();
}

void SirenBattleManager::Initialize() {
    unsigned char* fp = gf::GfDataBdat::getFP(0x3C);
    int top = Bdat::getIdTop(fp);
    int count = Bdat::getIdCount(fp);
    ::mm::mtl::FixStr<32> column;
    for (int id = top; id < top + count; id++) {
        Param& param = m_params[id - top];
        param.m_arrangeID = Bdat::getValCheck(fp, "ArrangeID", id, 2);
        param.m_gun = Bdat::getValCheck(fp, "Gun", id, 2);
        param.m_lance = Bdat::getValCheck(fp, "Lance", id, 2);
        param.m_gaugeBonus = (unsigned int)(unsigned short)Bdat::getValCheck(fp, "GaugeBonus", id, 2) * 0.01f;
        param.m_shotFrame = Bdat::getValCheck(fp, "ShotFrame", id, 1);
        param.m_damage[0] = 0.0f;
        param.m_gauge[0] = 1.0f;
        param.m_down[0] = 250;
        param.m_shotNum[0] = 0;
        for (int level = 1; level < 5; level++) {
            param.m_damage[level] =
                (unsigned int)(unsigned short)Bdat::getValCheck(fp, column.format("DamageLV%d", level).m_str, id, 2) * 0.01f;
            param.m_gauge[level] =
                (unsigned int)(unsigned short)Bdat::getValCheck(fp, column.format("GaugeLV%d", level).m_str, id, 2) * 0.01f;
            param.m_down[level] = Bdat::getValCheck(fp, column.format("DownLV%d", level).m_str, id, 1);
            param.m_shotNum[level] = Bdat::getValCheck(fp, column.format("ShotNumLV%d", level).m_str, id, 1);
        }
    }
    memset(m_cameraNames, 0, sizeof(m_cameraNames) + sizeof(m_positions));
    fp = gf::GfDataBdat::getFP(0x3D);
    top = Bdat::getIdTop(fp);
    count = Bdat::getIdCount(fp);
    for (int id = top; id < top + count; id++) {
        unsigned char situation = Bdat::getValCheck(fp, "situation", id, 1);
        const char*& camera = m_cameraNames[situation];
        m_positions[situation][0] = Bdat::getValCheck(fp, "Wpos", id, 2);
        camera = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "camera", id, 7));
        m_positions[situation][1] = Bdat::getValCheck(fp, "Bpos", id, 2);
        camera = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "camera", id, 7));
    }
}

void SirenBattleManager::Destroy() {
    SirenBattleManager* manager = SirenBattleManager::get();
    manager->Finalize();
    delete manager;
}

void SirenBattleManager::Finalize() {
    if (m_camera) {
        fw::CameraManager::get()->m_layers[0].pop(m_camera, 0.0f);
        m_camera = nullptr;
        pad_c0 = 0;
    }
    m_sides[0].reset();
    m_sides[1].reset();
    pad_d0 = 0;
    pad_c4 = -1.0f;
    pad_1c8 = 0xFF;
    pad_1c9 = 0xFF;
    pad_1ca = 0;
    pad_1cb = 0;
    pad_1cc = 0;
    gf::GfMenuManager::setDispAll(true);
}

void SirenBattleManager::NotifyMapChange() {
    Finalize();
}

bool SirenBattleManager::NotifyInputSpAttack() {
    if (!IsEnableSpAttack(true)) {
        return false;
    }
    {
        ::mm::mtl::FixedVector<unsigned char, 90> list;
        Utility::GetCharacterList(list, BattleGlobal::get()->m_controlHandle, static_cast<Utility::CHECK_CHR_NUM_MODE>(1), 2);
        CharacterManager* manager = CharacterManager::get();
        int voice = -1;
        for (unsigned char index : list) {
            const BattleCharacter* chr = manager->GetCharacterConst(index);
            if (chr->m_bdatID == 0x16) {
                voice = chr->m_voiceIndex;
                break;
            }
        }
        if (voice < 0) {
            int voices[3];
            int count = 0;
            for (unsigned char index : list) {
                const BattleCharacter* chr = manager->GetCharacterConst(index);
                if (chr->IsDriver(false)) {
                    voices[count++] = chr->m_voiceIndex;
                }
            }
            if (count > 0) {
                if (count == 1) {
                    voice = voices[0];
                } else {
                    voice = voices[ml::mtRand(count)];
                }
            }
        }
        if (voice >= 0) {
            int param = m_sides[0].pad_c;
            TalkManager::get()->NotifyTrigger(voice, TalkManager::TRIGGER(0x37), param, 0);
        }
    }
    pad_d0 = 13;
    return true;
}

bool SirenBattleManager::IsEnableSpAttack(bool flag) const {
    if (pad_1cc) {
        return false;
    }
    if (m_sides[!flag].m_gauge < 1.0f) {
        return false;
    }
    if (pad_d0 != 11) {
        return false;
    }
    if (!BattleGlobal::get()->IsEnableBattle() || BattleGlobal::get()->IsGameOver() || BattleGlobal::get()->IsPause(-1)) {
        return false;
    }
    if (BattleGlobal::get()->m_uniteComboCamera || BattleGlobal::get()->pad_bit12 ||
        BattleGlobal::get()->m_elementalCombo.m_camera || SpAttackManager::get()->m_camera) {
        return false;
    }
    if (ChainAttackManager::get()->IsProc(false)) {
        return false;
    }
    if (flag) {
        gf::GF_OBJ_HANDLE* driver = gf::GfGameParty::getHandleDriver(pad_1c9, gf::PTPOS(0));
        const BattleCharacter* character = CharacterManager::get()->GetCharacterConst(driver);
        if (character == nullptr || character->IsDead(0)) {
            return false;
        }
    }
    return true;
}

void SirenBattleManager::NotifyDownEnd(bool flag) {
    m_sides[!flag].pad_12_0 = 0;
}

void SirenBattleManager::NotifyLodFieldBreak(bool flag) {
    unsigned char bit = flag ? 0x8 : 0x10;
    if (pad_1ca & bit) {
        return;
    }
    pad_1ca |= bit;
    gf::GfFieldLod* lod = gf::GfFieldLod::sys();
    if (lod == nullptr) {
        return;
    }
    unsigned short lodId = flag ? 0xFCB : 0xFCC;
    int bdatId = lod->findBdatIdByLodId(lodId);
    if (bdatId != 0) {
        lod->setFade(bdatId, true, true);
        lod->setAnimReverse(bdatId, false, false);
    }
    lod = gf::GfFieldLod::sys();
    if (lod == nullptr) {
        return;
    }
    bdatId = lod->findBdatIdByLodId(lodId);
    ::mm::Mat44 mat;
    if (bdatId != 0 && lod->findTransform(mat, bdatId)) {
        ::mm::Vec3 pos = mat.getTrans();
        const char* name = flag ? "cmn_500_010" : "cmn_500_011";
        fw::EffectManager* effect = fw::EffectManager::get();
        unsigned int handle = effect->create(name, nullptr, true);
        effect->setParam(handle, pos, ::mm::Vec3(1.0f, 1.0f, 1.0f));
    }
}

void SirenBattleManager::PreUpdate(const fw::UpdateInfo& info) {}

void SirenBattleManager::Update(const fw::UpdateInfo& info) {
    get()->UpdateProc(info);
}

bool SirenBattleManager::GetSituationPointData(SITUATION_POINT_DATA& data, int situation, bool flag) const {
    ::mm::Vec3 rot;
    if (!gf::GfGameUtil::getGmkPointPosRot(gmk::GmkType(0x35), m_positions[situation][!flag], data.m_pos, rot)) {
        return false;
    }
    ::mm::Mat44 mat;
    mat.setRotXYZ(rot);
    const ::mm::Vec3& dir = ::mm::Vec3::unitZ;
    data.m_dir = ::mm::Vec3(mat.m[0][0] * dir.x + mat.m[1][0] * dir.y + mat.m[2][0] * dir.z + mat.m[3][0],
                            mat.m[0][1] * dir.x + mat.m[1][1] * dir.y + mat.m[2][1] * dir.z + mat.m[3][1],
                            mat.m[0][2] * dir.x + mat.m[1][2] * dir.y + mat.m[2][2] * dir.z + mat.m[3][2]);
    return true;
}

const char* SirenBattleManager::GetSituationCameraName(int situation) const {
    return m_cameraNames[situation];
}

bool SirenBattleManager::GetShootBulletNum(bool flag) const {
    return m_sides[!flag].pad_d;
}

float SirenBattleManager::GetShootBulletIntrevalSec(bool flag) const {
    return m_params[!flag].m_shotFrame * (1.0f / 30.0f);
}

void SirenBattleManager::SetSirenObject(const BattleCharacter* character) {
    if (pad_1cb) {
        return;
    }
    int id = character->m_bdatID;
    Side* side;
    if (m_params[0].m_arrangeID == id) {
        side = &m_sides[0];
    } else if (m_params[1].m_arrangeID == id) {
        side = &m_sides[1];
    } else {
        return;
    }
    side->m_handle = character->m_handle;
    side->pad_10 = character->m_voiceIndex;
    if (m_sides[0].m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) &&
        m_sides[1].m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        pad_d0 = 1;
    }
}

bool SirenBattleManager::IsRegisterSiren() const {
    return m_sides[0].m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) ||
           m_sides[1].m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

void SirenBattleManager::SetGimmickCamera(::mm::mtl::IntrusivePtr<fw::Camera> camera) {
    if (m_camera) {
        fw::CameraManager::get()->m_layers[0].pop(m_camera, 0.0f);
        m_camera = nullptr;
        pad_c0 = 0;
    }
    m_camera = camera;
    pad_c0 = 0;
}

bool SirenBattleManager::IsCameraProc() const {
    if (pad_1cb) {
        if (m_camera) {
            return true;
        }
        if (pad_d0 >= 12 && pad_d0 <= 18) {
            return true;
        }
        if (TalkManager::get()->IsTalkSirenSp()) {
            return true;
        }
    }
    return false;
}

float SirenBattleManager::GetDamageBonus(bool flag) const {
    float rate = 0.0f;
    if (pad_1cb && !m_sides[!flag].pad_12_0) {
        Param param = m_params[!flag];
        rate = param.m_damage[m_sides[!flag].m_level];
    }
    return rate;
}

float SirenBattleManager::GetGaugeRate(bool flag) const {
    float rate = 1.0f;
    if (pad_1cb && !pad_1cc) {
        const Side& side = m_sides[!flag];
        if (side.pad_12_0) {
            rate = 0.0f;
        } else {
            Param param = m_params[!flag];
            rate = param.m_gauge[side.m_level];
            if (side.pad_12_1) {
                rate = param.m_gauge[side.m_level] * param.m_gaugeBonus;
            }
        }
    }
    return rate;
}

void SirenBattleManager::AddSirenSpGaugeRate(float value, bool flag) {
    if (IsCameraProc()) {
        return;
    }
    Side& side = m_sides[!flag];
    if (side.pad_12_0) {
        return;
    }
    union {
        float f;
        int i;
    } add;
    add.f = GetGaugeRate(flag) * value;
    add.i += 1;
    float gauge = side.m_gauge + add.f;
    if (side.pad_e) {
        int party = gauge * 300.0f;
        DataManager::get()->SetPartyGauge(party, false);
    }
    side.m_gauge = ::mm::clamp(gauge, 0.0f, 1.0f);
}

}  // namespace btl

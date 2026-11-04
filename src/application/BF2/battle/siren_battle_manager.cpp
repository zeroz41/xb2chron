#include "btl/siren_battle_manager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/TalkManager.h"
#include "classes/fw/Camera.h"
#include "classes/fw/CameraManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuManager.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include <string.h>

namespace btl {

SirenBattleManager::~SirenBattleManager() {}

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
        m_positions[situation].m_wpos = Bdat::getValCheck(fp, "Wpos", id, 2);
        camera = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "camera", id, 7));
        m_positions[situation].m_bpos = Bdat::getValCheck(fp, "Bpos", id, 2);
        camera = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "camera", id, 7));
    }
}

void SirenBattleManager::Destroy() {
    SirenBattleManager* manager = SirenBattleManager::get();
    manager->Finalize();
    delete manager;
}

void SirenBattleManager::NotifyMapChange() {
    Finalize();
}

void SirenBattleManager::NotifyDownEnd(bool flag) {
    m_sides[!flag].pad_12_0 = 0;
}

void SirenBattleManager::PreUpdate(const fw::UpdateInfo& info) {}

void SirenBattleManager::Update(const fw::UpdateInfo& info) {
    get()->UpdateProc(info);
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

}  // namespace btl

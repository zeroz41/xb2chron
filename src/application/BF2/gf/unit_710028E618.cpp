#include "classes/gf/GfArenaReward.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/SCOM_BATTLE_ARENA.h"
#include "classes/gf/GimmickCamera.h"
#include "classes/fw/CameraManager.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkBattleChallengeReward.h"
#include "classes/gmk/GmkBattleChallengeRewardList.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfFobjDropitem.h"
#include "classes/fw/FrameworkMemory.h"
#include "plugin/Bdat.h"

namespace gf {

GfArenaReward::GfArenaReward(GfGameArena* owner) : m_owner(owner) {}

GfArenaReward::~GfArenaReward() {}

void GfArenaReward::createTresureBox(const ArenaBattleInfo& info) {
    unsigned int num = getTresureBoxNum(info);
    Bdat::uVal wait;
    wait.ulong = Bdat::getValCheck(GfDataBdat::getFP(0x7B), 0, 0x51, 8);
    unsigned int max = m_gmks.size();
    unsigned int count = num < max ? num : max;
    for (unsigned int i = 0; i < count; i++) {
        gmk::GmkBattleChallengeReward* box = static_cast<gmk::GmkBattleChallengeReward*>(m_gmks[i]);
        box->m_bdatRow = info.m_id;
        box->m_index = i;
        box->initWaitPopTime(wait.real * i);
    }
}

int GfArenaReward::getTresureBoxNum(const ArenaBattleInfo& score) const {
    GfBdatBtl* btl = GfBdatBtl::get();
    return (btl->getBTL_ChBtlTresureNeed(score.m_id, 0) <= score.m_value) + (btl->getBTL_ChBtlTresureNeed(score.m_id, 1) <= score.m_value) +
           (btl->getBTL_ChBtlTresureNeed(score.m_id, 2) <= score.m_value);
}

bool GfArenaReward::getActionOrigin(mm::Mat44& mtx) const {
    if (m_gmks.size() != 0) {
        (*m_gmks.begin())->getMatrix(mtx, true);
        return true;
    }
    return false;
}

void GfArenaReward::createCameraCut01(const mm::Vec3& pos, float rotY) {
    m_camera = GimmickCamera::create("salvage_cut01", pos, rotY);
    static_cast<GimmickCamera*>(m_camera.get())->setAuto(false);
}

void GfArenaReward::destroyCameraCut01() {
    fw::CameraManager* manager = fw::CameraManager::get();
    if (m_camera && m_camera->m_pushed) {
        manager->m_layers[0].pop(m_camera, 1.0f);
    }
    m_camera = nullptr;
}

void GfArenaReward::playCameraCut01() {
    if (m_camera && !m_camera->m_pushed) {
        fw::CameraManager::get()->m_layers[0].push(m_camera, 0.0f);
        if (m_camera) {
            static_cast<GimmickCamera*>(m_camera.get())->play();
        }
    }
}

void GfArenaReward::listUpTBox() {
    m_gmks.clear();
    gmk::GmkManager* manager = gmk::GmkManager::sys();
    for (gmk::GmkSet* const* it = manager->m_gmkSets.begin(); it != manager->m_gmkSets.end(); ++it) {
        gmk::GmkBattleChallengeRewardList* list =
            static_cast<gmk::GmkBattleChallengeRewardList*>((*it)->getGmkList(gmk::GmkBattleChallengeReward::TYPE));
        if (list == nullptr) {
            continue;
        }
        unsigned int num = list->getInstNum();
        for (unsigned int i = 0; i < num; i++) {
            m_gmks.push_back(&list->m_gmks[i]);
            if (m_gmks.size() == 8) {
                break;
            }
        }
    }
}

void GfArenaReward::playVoice(const ArenaBattleInfo& score) {
    SCOM_BATTLE_ARENA::createAfterVoice(getTresureBoxNum(score));
}

void GfArenaReward::playReturnVoice(bool flag) {
    GF_OBJ_HANDLE* handles[3];
    unsigned int count = 0;
    for (unsigned int i = 0; i < 3; ++i) {
        handles[i] = GfGameParty::getHandleDriver(i, static_cast<PTPOS>(0));
        if (handles[i] != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            ++count;
        }
    }
    SCOM_BATTLE_ARENA::createReturnVoice(handles, count != 0, flag);
}

void GfArenaReward::dropClearReward(const ArenaBattleInfo& info) {
    unsigned int itemId = GfBdatBtl::get()->getBTL_ChBtlClearReward(info.m_id);
    if (itemId != 0) {
        GfFobjDropitem::EmitInfo emit;
        emit.m_items.setAllocator(fw::FrameworkMemory::getAllocator(5));
        emit.m_items.reserve(1);
        GfDropitemInfo item;
        item.pad_0x0 = itemId;
        item.pad_0x4 = 1;
        item.pad_0x5 = 100;
        item.pad_0x8 = 0;
        item.pad_0xc = 0;
        item.pad_0x10 = 0.0f;
        emit.m_items.push_back(item);
        GfFobjDropitem::emitDropitems(emit);
    }
}

}  // namespace gf

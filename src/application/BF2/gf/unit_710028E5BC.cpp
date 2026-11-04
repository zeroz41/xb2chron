#include "classes/gf/GfArenaReward.h"
#include "classes/gf/GfArenaParty.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/GimmickCamera.h"
#include "classes/fw/CameraManager.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gf/DataParamAcc.h"

namespace gf {

unsigned int GfArenaParty::fn_710028E5BC(const GfGameManager::BattleChallengeRecord::Key& key, GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    return key.fn_7100290AE4(acc.getBlade(-1, false));
}

GfArenaReward::GfArenaReward(GfGameArena* owner) : m_owner(owner) {}

GfArenaReward::~GfArenaReward() {}

int GfArenaReward::fn_710028E7DC(const GfArenaBattle::Score& score) {
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

void GfArenaReward::fn_710028EF70(const GfArenaBattle::Score& score) {
    fn_710056B988(fn_710028E7DC(score));
}

void GfArenaReward::playReturnVoice(bool flag) {
    GF_OBJ_HANDLE* handles[3];
    unsigned int count = 0;
    for (unsigned int i = 0; i < 3; ++i) {
        handles[i] = GfGameParty::getHandleDriver(i, 0);
        if (handles[i] != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            ++count;
        }
    }
    fn_710056B9CC(handles, count != 0, flag);
}

}  // namespace gf

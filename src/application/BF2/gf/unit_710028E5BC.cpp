#include "classes/gf/TUnk_28E618.h"
#include "classes/gf/TUnk_28D7B8.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/GimmickCamera.h"
#include "classes/fw/CameraManager.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gf/DataParamAcc.h"

namespace gf {

unsigned int TUnk_28D7B8::fn_710028E5BC(const GfGameManager::BattleChallengeRecord::Key& key, GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    return key.fn_7100290AE4(acc.getBlade(-1, false));
}

TUnk_28E618::TUnk_28E618(TUnk_B535D0* owner) : m_owner(owner) {}

TUnk_28E618::~TUnk_28E618() {}

int TUnk_28E618::fn_710028E7DC(const TUnk_B52C38::Score& score) {
    GfBdatBtl* btl = GfBdatBtl::get();
    return (btl->fn_71001EA2E8(score.m_id, 0) <= score.m_value) + (btl->fn_71001EA2E8(score.m_id, 1) <= score.m_value) +
           (btl->fn_71001EA2E8(score.m_id, 2) <= score.m_value);
}

bool TUnk_28E618::fn_710028EB74(mm::Mat44& mtx) const {
    if (m_gmks.size() != 0) {
        (*m_gmks.begin())->getMatrix(mtx, true);
        return true;
    }
    return false;
}

void TUnk_28E618::fn_710028EBB0(const mm::Vec3& pos, float rotY) {
    m_camera = GimmickCamera::create("salvage_cut01", pos, rotY);
    static_cast<GimmickCamera*>(m_camera.get())->setAuto(false);
}

void TUnk_28E618::fn_710028ECA0() {
    fw::CameraManager* manager = fw::CameraManager::get();
    if (m_camera && m_camera->m_pushed) {
        manager->m_layers[0].pop(m_camera, 1.0f);
    }
    m_camera = nullptr;
}

void TUnk_28E618::fn_710028ED50() {
    if (m_camera && !m_camera->m_pushed) {
        fw::CameraManager::get()->m_layers[0].push(m_camera, 0.0f);
        if (m_camera) {
            static_cast<GimmickCamera*>(m_camera.get())->play();
        }
    }
}

void TUnk_28E618::fn_710028EF70(const TUnk_B52C38::Score& score) {
    fn_710056B988(fn_710028E7DC(score));
}

void TUnk_28E618::fn_710028F00C(bool flag) {
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

#include "gf/FileStaticVec3.h"
#include "classes/gf/pc/LookAtPlugin.h"
#include "gf/GfSearchParam.h"
#include "classes/fw/LookIkSolver.h"
#include "classes/fw/ParamList.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfComIK.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfGameSearchObj.h"
#include "classes/gf/GfObj.h"
#include "classes/fw/ComponentObject.h"
#include "fw/UpdateInfo.h"
#include "gf/GfObjUtil.h"
#include "gf/LookParam.h"
#include "gf/MsgPcGetLookPoint.h"

namespace gf { namespace pc {

LookAtPlugin::LookAtPlugin()
    : m_solver(), m_paramList(), m_searchObj(reinterpret_cast<gf::GF_SEARCH_OBJ*>(-1)),
      m_targets(getAllocator(ALLOCATOR(0))), m_current(nullptr), m_lookState(0), m_changeWait(0.0f), m_typeWaits() {}

LookAtPlugin::~LookAtPlugin() {}

// setup (0x7100519A0C) is not matched yet: its candidate is in the worker's wip (40 words differ)

void LookAtPlugin::cleanup(gf::GfComBehaviorPc&) {
    if (m_searchObj != reinterpret_cast<gf::GF_SEARCH_OBJ*>(-1)) {
        GfGameSearchObj::destroyObj(m_searchObj);
        m_searchObj = reinterpret_cast<gf::GF_SEARCH_OBJ*>(-1);
    }
    m_solver = nullptr;
}

void LookAtPlugin::onActivate() {
    m_current = nullptr;
    m_targets.clear();
    m_typeWaits[4] = 0.0f;
    m_typeWaits[0] = 0.0f;
    m_typeWaits[1] = 0.0f;
    m_typeWaits[2] = 0.0f;
    m_typeWaits[3] = 0.0f;
    m_lookState = 0;
    m_changeWait = 0.0f;
}

void LookAtPlugin::onDeactivate() {
    const LookParam* param = m_paramList->getAdapter(4).get<LookParam>();
    if (m_current != nullptr) {
        m_solver->fadeOut(param->fadeOutTime);
    }
}

void LookAtPlugin::update(gf::GfComBehaviorPc& behavior, const fw::UpdateInfo& info) {
    updateHoldHandles(behavior);
    for (int i = 0; i < 5; i++) {
        if (m_typeWaits[i] > 0.0f) {
            m_typeWaits[i] -= info.m_deltaTime;
        }
    }
    if (m_changeWait > 0.0f) {
        m_changeWait -= info.m_deltaTime;
    }
    if (m_changeWait <= 0.0f && changeTarget()) {
        m_changeWait = m_current->m_lookInfo->m_lookTime;
    }
    if (m_current == nullptr) {
        m_lookState = 0;
    } else {
        GfObj* target = GfObjUtil::getObj(m_current->m_handle);
        if (target != nullptr) {
            MsgPcGetLookPoint msg;
            if (static_cast<GfObj*>(behavior.m_owner)->sendMessage(target, msg)) {
                m_solver->setTarget(msg.m_point);
            }
        }
    }
}

void LookAtPlugin::onReloadBdat() {
    GfBdatLookAt* bdat = GfBdatLookAt::get();
    GfSearchParam* search = GfGameSearchObj::getInfo(m_searchObj);
    search->m_radius = bdat->getMaxRadius();
    search->m_checks |= GfSearchParam::CHECK_RADIUS;
    float up = bdat->getMaxUpper();
    float down = bdat->getMaxLower();
    search->m_checks |= GfSearchParam::CHECK_HEIGHT;
    search->m_heightUp = up;
    search->m_heightDown = down;
}

mm::mtl::RTTI LookAtPlugin::m_rtti("LookAtPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc

// updateHoldHandles (not written yet) adds and drops targets
template void mm::mtl::Map<gf::GF_OBJ_HANDLE*, gf::pc::LookAtPlugin::TargetInfo>::tree_type::erase(mm::mtl::Map<gf::GF_OBJ_HANDLE*, gf::pc::LookAtPlugin::TargetInfo>::node*);
template void mm::mtl::Map<gf::GF_OBJ_HANDLE*, gf::pc::LookAtPlugin::TargetInfo>::tree_type::rebalance_after_erase(mm::mtl::Map<gf::GF_OBJ_HANDLE*, gf::pc::LookAtPlugin::TargetInfo>::node*);
template mm::mtl::Map<gf::GF_OBJ_HANDLE*, gf::pc::LookAtPlugin::TargetInfo>::node* mm::mtl::Map<gf::GF_OBJ_HANDLE*, gf::pc::LookAtPlugin::TargetInfo>::tree_type::insert(const mm::mtl::Map<gf::GF_OBJ_HANDLE*, gf::pc::LookAtPlugin::TargetInfo>::tree_type::value_type&);

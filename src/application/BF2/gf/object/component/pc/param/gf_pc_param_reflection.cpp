#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/AccessPlugin.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/SCOM_ACCESS_TARGET.h"
#include "gf/AccessParam.h"
#include "gf/MsgPcFieldGetAccessType.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/pc/StateUtil.h"
#include "gf/FileStaticVec3.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfObj.h"

namespace gf { namespace pc {

AccessPlugin::AccessPlugin()
    : m_target(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_behavior(nullptr), m_accessKinds(-1) {}

bool AccessPlugin::setup(gf::GfComBehaviorPc& behavior) {
    m_paramList = fw::ParamManager::get()->m_paramLists[5];
    m_behavior = &behavior;
    return true;
}

void AccessPlugin::cleanup(gf::GfComBehaviorPc&) {
    if (m_target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        SCOM_ACCESS_TARGET::create(m_target);
    }
}

void AccessPlugin::onDeactivate() {
    if (m_target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        SCOM_ACCESS_TARGET::create(m_target);
    }
}

// update (0x7100516C54) is not matched yet: its last step keeps two stores of the target where the candidate
// compiles one select; isActiveRange (0x7100516DBC) calls GfObjAcc's fn_710052478C, which has no name yet;
// drawDebug (0x7100516FD4) stores the matrix's [2][2] and [2][3] as one word

void AccessPlugin::onActivate() {}

mm::mtl::RTTI AccessPlugin::m_rtti("AccessPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc

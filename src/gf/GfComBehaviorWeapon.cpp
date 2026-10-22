#include "gf/FileStaticVec3.h"
#include "gf/GfObjUtil.h"
#include "gf/MsgObjectForceWeaponMount.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/SCOM_OBJ_ALPHA.h"
#include "classes/gf/GfComBehaviorWeapon.h"
#include "anm/AsmAnnotetion.h"
#include "gf/MsgObjectNotifyAsmCallback.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Vector.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfObj.h"
#include "classes/fw/UpdatableObject.h"
#include "fw/Message.h"
#include "string.h"

namespace gf {

bool GfComBehaviorWeapon::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    switch (msg.m_id) {
    case 0x1000042:
        procMsgObjectNotifyAsmCallback(sender, static_cast<MsgObjectNotifyAsmCallback&>(msg));
        break;
    case 0x1000043:
        procMsgObjectOnChangeWeapon(sender, static_cast<MsgObjectForceWeaponMount&>(msg));
        break;
    default:
        return false;
    }
    return true;
}

void GfComBehaviorWeapon::procMsgObjectNotifyAsmCallback(fw::MessageObject* sender, MsgObjectNotifyAsmCallback& msg) {
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    if (asmCom == nullptr) {
        return;
    }
    const anm::AsmAnnotetion* annotation = msg.m_annotation;
    if (strcmp(annotation->m_name, "weaponTrans") == 0) {
        if (annotation->m_type == 1) {
            m_commands.push_back(annotation->m_text);
        }
    } else if (strcmp(annotation->m_name, "battleStartEnd") == 0 && annotation->m_type == 1) {
        GfFadeInfo info;
        if (GfObjUtil::parseFadeParam(annotation->m_text, &info)) {
            float invFps = 0.0f;
            asmCom->getClipInvFps(asmCom->getStateName(AnimLayer(0)), 0, &invFps);
            float time = info.m_frames * invFps;
            if (info.m_type == 0) {
                SCOM_OBJ_ALPHA::create(static_cast<GfObj*>(m_owner)->m_handle, time, 1.0f);
            } else if (info.m_type == 1) {
                SCOM_OBJ_ALPHA::create(static_cast<GfObj*>(m_owner)->m_handle, time, 0.0f);
            }
        }
    }
}

void GfComBehaviorWeapon::procMsgObjectOnChangeWeapon(fw::MessageObject* sender, MsgObjectForceWeaponMount& msg) {
    mm::mtl::FixStr<64> state("S_");
    if (const char* motion = GfObjUtil::getMotionResourceName(msg.m_handle)) {
        state += motion + 3;
        state += "_";
    }
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    if (asmCom == nullptr) {
        return;
    }
    switch (msg.m_mount) {
    case 0:
    case 2:
    case 4:
        state += "idle";
        break;
    case 1:
    case 3:
        state += "btidle";
        break;
    default:
        return;
    }
    asmCom->setState(state.m_str, AnimLayer(0));
}

GfComBehaviorWeapon::GfComBehaviorWeapon() : m_commands(getAllocator(ALLOCATOR(0))) {}

GfComBehaviorWeapon::~GfComBehaviorWeapon() {}

void GfComBehaviorWeapon::update(const fw::UpdateInfo& info) {
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    if (asmCom == nullptr) {
        return;
    }
    for (unsigned int i = 0; i < m_commands.size(); i++) {
        if (!asmCom->execCmd(m_commands[i], AnimLayer(0))) {
            asmCom->getStateName(AnimLayer(0));
        }
    }
    m_commands.clear();
}

void GfComBehaviorWeapon::changeLayer(unsigned int, unsigned int) {}

mm::mtl::RTTI GfComBehaviorWeapon::m_rtti("GfComBehaviorWeapon", &GfComBehavior::m_rtti, nullptr);

}  // namespace gf

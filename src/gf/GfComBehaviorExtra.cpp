#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComBehaviorExtra.h"
#include "anm/AsmAnnotetion.h"
#include "gf/MsgObjectNotifyAsmCallback.h"
#include "mm/mtl/Vector.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/fw/UpdatableObject.h"
#include "fw/Message.h"
#include "string.h"

namespace gf {

bool GfComBehaviorExtra::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    switch (msg.m_id) {
    case 0x1000042:
        procMsgObjectNotifyAsmCallback(sender, static_cast<MsgObjectNotifyAsmCallback&>(msg));
        break;
    case 0x1000022:
        if (GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2)) {
            asmCom->execCmd("C_schedule_00_00", AnimLayer(0));
        }
        break;
    default:
        return false;
    }
    return true;
}

void GfComBehaviorExtra::procMsgObjectNotifyAsmCallback(fw::MessageObject* sender, MsgObjectNotifyAsmCallback& msg) {
    if (m_owner->getComponent<GfComAsm>(2) == nullptr) {
        return;
    }
    const anm::AsmAnnotetion* annotation = msg.m_annotation;
    if (strcmp(annotation->m_name, "attachmentTrans") == 0 && annotation->m_type == 1) {
        m_commands.push_back(annotation->m_text);
    }
}

GfComBehaviorExtra::GfComBehaviorExtra() : m_commands(getAllocator(ALLOCATOR(0))) {}

GfComBehaviorExtra::~GfComBehaviorExtra() {}

void GfComBehaviorExtra::setup() {}

void GfComBehaviorExtra::cleanup() {}

void GfComBehaviorExtra::update(const fw::UpdateInfo& info) {
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    if (asmCom == nullptr) {
        return;
    }
    for (unsigned int i = 0; i < m_commands.size(); i++) {
        asmCom->execCmd(m_commands[i], AnimLayer(0));
    }
    m_commands.clear();
}

mm::mtl::RTTI GfComBehaviorExtra::m_rtti("GfComBehaviorExtra", &GfComBehavior::m_rtti, nullptr);

}  // namespace gf

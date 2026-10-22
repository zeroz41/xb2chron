#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfComProperty.h"
#include "gf/GfObjUpdate.h"
#include "gf/GfObjUtil.h"
#include "fw/Message.h"
#include "fw/ObjectEvent.h"
#include "gf/MsgDebugActivateObjectWindow.h"
#include "gf/MsgDebugDeactivateObjectWindow.h"

namespace gf {

GfObj::GfObj(unsigned int type, const fw::HandlePtr<fw::UpdatableObject>& handle, unsigned int arg)
    : fw::UpdatableObject(type, handle, arg),
      m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)),
      m_info(nullptr),
      pad_108(),
      m_updateFlags(0),
      m_execUpdate(false) {}

GfObj::~GfObj() {}

void GfObj::update(const fw::UpdateInfo& info) {
    m_updateFlags |= 1;
    GfObjUpdate::updateComponent(this, info);
    m_updateFlags &= ~1;
}

void GfObj::onEvent(const fw::ObjectEvent& event) {
    if (event.m_type == 0) {
        if (GfComProperty* property = getComponent<GfComProperty>(5)) {
            property->flush();
        }
    }
}

bool GfObj::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    for (unsigned long i = 0; i < 12; i++) {
        if (msg.m_category & (1 << i)) {
            if (GfComponent* component = getComponent<GfComponent>(i)) {
                return component->recieveMessage(sender, msg);
            }
        }
    }
    // the original tests 0x1000002 first: clang lowers the chain to a switch, testing in reverse source order
    if (msg.m_id == MsgDebugActivateObjectWindow::ID) {
        procMsgActivateObjectDebugWindow(sender, static_cast<MsgDebugActivateObjectWindow&>(msg));
        return true;
    }
    if (msg.m_id == MsgDebugDeactivateObjectWindow::ID) {
        procMsgDeactivateObjectDebugWindow(sender, static_cast<MsgDebugDeactivateObjectWindow&>(msg));
        return true;
    }
    return false;
}

// 1.0.0's (names from its symbols); empty there, and dropped by 3.0.1's linker once inlined
void GfObj::procMsgActivateObjectDebugWindow(fw::MessageObject* sender, MsgDebugActivateObjectWindow& msg) {}

void GfObj::procMsgDeactivateObjectDebugWindow(fw::MessageObject* sender, MsgDebugDeactivateObjectWindow& msg) {}

void GfObj::setUpdateComponent(bool on) {
    if (on) {
        m_updateFlags |= 2;
    } else {
        m_updateFlags &= ~2;
    }
    GfObjUtil::applyExecUpdate(this);
}

void GfObjLayerSpeed::initialize() {
    for (int i = 0; i < 32; i++) {
        s_info[i] = Info();
    }
}

void GfObjLayerSpeed::finalize() {}

void GfObjLayerSpeed::reqApplyModelLayerSpeed(unsigned int layer, float speed) {
    s_info[layer].m_request = true;
    s_info[layer].m_speed = speed;
}

bool GfObjLayerSpeed::isRequest(unsigned int layer) {
    return s_info[layer].m_request;
}

float GfObjLayerSpeed::getSpeed(unsigned int layer) {
    return s_info[layer].m_speed;
}

void GfObjLayerSpeed::cleanup() {
    for (int i = 0; i < 32; i++) {
        s_info[i] = Info();
    }
}

mm::mtl::RTTI GfObj::m_rtti("GfObj", &fw::UpdatableObject::m_rtti, &fw::MessageObject::m_rtti);
GfObjLayerSpeed::Info GfObjLayerSpeed::s_info[32];

}  // namespace gf

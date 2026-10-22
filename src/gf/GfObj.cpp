#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComProperty.h"
#include "gf/GfObjUpdate.h"
#include "gf/GfObjUtil.h"
#include "fw/Message.h"
#include "fw/ObjectEvent.h"

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

// recieveMessage (0x7100521BE0, and its thunk) is not here yet: written as the loop over the 12 component slots
// (the message's category bits) handing the message to the first GfComponent, then
// 'return msg.m_id == 0x1000002 || msg.m_id == 0x1000001', the loop is identical but clang folds the two tests into
// one range check where the original tests 0x1000002, then 0x1000001

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

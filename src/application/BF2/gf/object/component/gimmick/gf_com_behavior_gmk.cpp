#include "gf/FileStaticVec3.h"
#include "classes/fw/IColiEventListener.h"
#include "classes/fw/ColiUserData.h"
#include "classes/fw/ColiObject.h"
#include "classes/gf/GfComCollider.h"
#include "classes/gf/GfComBehaviorGmk.h"
#include "classes/gf/GfMenuObjTargetInfo.h"
#include "classes/fw/ColiMoveObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gmk/AGmkBase.h"
#include "gf/MsgPcFieldGetAccessType.h"
#include "classes/gf/GfObj.h"
#include "gf/MsgPcGetLookPoint.h"
#include "gf/MsgPcFieldNotifyAction.h"
#include "gf/MsgPcFieldNotifySkillEvent.h"
#include "gf/MsgPcGetElvLift.h"

namespace gf {

// 1.0.0 had these two out of line; 3.0.1 has them only inlined into recieveMessage
inline void GfComBehaviorGmk::procMsgPcFieldGetAccessType(fw::MessageObject* sender, MsgPcFieldGetAccessType& msg) {
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
    if (gmk == nullptr) {
        return;
    }
    switch (gmk->getGmkType()) {
    case 9:
    case 0x1C:
    case 0x3C:
        msg.m_type = 1;
        break;
    case 0x1F:
        msg.m_type = 5;
        msg.m_salvage = true;
        break;
    case 0x20:
        msg.m_type = *gmk->m_createInfo.m_data == 2 ? 1 : 5;
        break;
    case 0x25:
        msg.m_type = 3;
        break;
    case 0x26:
        msg.m_type = 4;
        break;
    default:
        msg.m_type = 5;
        break;
    }
}

inline void GfComBehaviorGmk::procMsgPcGetLookPoint(fw::MessageObject* sender, MsgPcGetLookPoint& msg) {
    msg.m_point = m_frame->getWorldTransform().position;
    msg.m_found = true;
}

bool GfComBehaviorGmk::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    switch (msg.m_id) {
    case 0x1000008:
        procMsgPcGetLookPoint(sender, static_cast<MsgPcGetLookPoint&>(msg));
        return true;
    case 0x100000C:
        procMsgPcFieldGetAccessType(sender, static_cast<MsgPcFieldGetAccessType&>(msg));
        return true;
    case 0x100000D:
        procMsgPcFieldNotifyAction(sender, static_cast<MsgPcFieldNotifyAction&>(msg));
        return true;
    case 0x100001E:
        procMsgPcFieldNotifySkillEvent(sender, static_cast<MsgPcFieldNotifySkillEvent&>(msg));
        return true;
    case 0x1000027:
        procMsgPcGetElvLift(sender, static_cast<MsgPcGetElvLift&>(msg));
        return true;
    }
    return false;
}

GfComBehaviorGmk::GfComBehaviorGmk()
    : m_coliObject(nullptr), m_routeNavi(nullptr), m_menuContext(nullptr), m_bigObj(nullptr) {}

void GfComBehaviorGmk::cleanup() {
    disposeMenuObj();
    m_frame = nullptr;
}

void GfComBehaviorGmk::disposeMenuObj() {
    if (m_menuContext != nullptr) {
        GfMenuObjTargetInfo::close(m_menuContext);
        if (m_menuContext != nullptr) {
            m_menuContext->release();
            m_menuContext = nullptr;
        }
    }
}

fw::ColiMoveObject* GfComBehaviorGmk::getColiObject() const {
    const GfComCollider* collider = m_owner->getComponent<GfComCollider>(4);
    if (collider != nullptr && collider->m_coliObjects.size() != 0) {
        fw::ColiObject* coli = collider->m_coliObjects[0];
        if (coli != nullptr) {
            return coli->getRTTI()->isKindOf(&fw::ColiMoveObject::m_rtti) ? static_cast<fw::ColiMoveObject*>(coli)
                                                                         : nullptr;
        }
    }
    return nullptr;
}

mm::mtl::RTTI GfComBehaviorGmk::m_rtti("GfComBehaviorGmk", &GfComBehavior::m_rtti, nullptr);

}  // namespace gf

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
#include "gf/GfObjAcc.h"
#include "gf/GfPlayFactory.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfObjSetupMapLodAnim.h"
#include "classes/gmk/GmkElevator.h"
#include "classes/gmk/GmkJump.h"
#include "classes/gmk/GmkWarp.h"
#include "classes/gmk/GmkRouteNavi.h"
#include "classes/gmk/GmkCollection.h"
#include "classes/gmk/GmkCamp.h"
#include "classes/gmk/GmkSalvage.h"
#include "classes/gf/GfObjSetupGimmick.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfGameUtil.h"
#include "gf/GfMenuBdat.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfComTransform.h"
#include "fw/UpdateInfo.h"
#include "math.h"

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

void GfComBehaviorGmk::procMsgPcFieldNotifyAction(fw::MessageObject* sender, MsgPcFieldNotifyAction& msg) {
    if (msg.m_action != 0 || !(static_cast<GfObj*>(m_owner)->pad_110 & 1)) {
        return;
    }
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
    if (gmk == nullptr) {
        // only the calls of a stripped debug report are left
        GfObjAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
        acc.isDestroy();
        acc.testFlag(0xe);
        return;
    }
    bool access;
    switch (gmk->getGmkType()) {
    case 9:
    case 0x20:
    case 0x3c:
        access = GfPlayFactory::createFieldTbox(static_cast<GfObj*>(m_owner)->m_handle);
        break;
    case 0x1c:
        access = GfPlayFactory::createCollect(static_cast<GfObj*>(m_owner)->m_handle);
        break;
    case 0x1f:
        access = GfPlayFactory::createSalvage(static_cast<GfObj*>(m_owner)->m_handle);
        break;
    case 0x21:
        access = GfPlayFactory::createMapGimmick(static_cast<GfObj*>(m_owner)->m_handle);
        break;
    case 0x23:
        access = GfPlayFactory::createGrave(static_cast<GfObj*>(m_owner)->m_handle);
        break;
    case 0x25:
        access = GfPlayFactory::createJump(static_cast<GfObj*>(m_owner)->m_handle);
        break;
    case 0x26:
        access = GfPlayFactory::createWarp(static_cast<GfObj*>(m_owner)->m_handle);
        break;
    case 0x29:
    case 0x2a:
        access = GfGameManager::isEnableFieldAccess();
        break;
    case 10:
    case 0x24:
    case 0x3a:
    case 0x3e:
        access = true;
        break;
    default:
        return;
    }
    if (access) {
        gmk->onPlayerAccessed(static_cast<GfObj*>(m_owner)->m_handle);
    }
}

void GfComBehaviorGmk::procMsgPcFieldNotifySkillEvent(fw::MessageObject* sender, MsgPcFieldNotifySkillEvent& msg) {
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
    if (gmk == nullptr) {
        return;
    }
    int event = msg.m_event;
    switch (gmk->getGmkType()) {
    case gmk::GmkJump::TYPE:
        if (event == 0) {
            static_cast<gmk::GmkJump*>(gmk)->reqDeadIcon();
            return;
        }
        static_cast<gmk::GmkJump*>(gmk)->reqRecreateIcon();
        break;
    case gmk::GmkWarp::TYPE:
        if (event == 0) {
            static_cast<gmk::GmkWarp*>(gmk)->reqDeadIcon();
            return;
        }
        static_cast<gmk::GmkWarp*>(gmk)->reqRecreateIcon();
        break;
    default:
        return;
    }
    createMenuObj();
}

void GfComBehaviorGmk::procMsgPcGetElvLift(fw::MessageObject* sender, MsgPcGetElvLift& msg) {
    msg.m_lifts.clear();
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
    if (gmk == nullptr || gmk->getGmkType() != gmk::GmkElevator::TYPE) {
        return;
    }
    unsigned short liftLod = static_cast<const gmk::GmkElevator::BdatInfo*>(gmk->m_createInfo.m_bdatInfo)->m_liftLod;
    if (const GfFieldLod::BdatInfo* lodInfo = mm::mtl::PtrSingleton<GfFieldLod>::get()->findBdatInfo(liftLod)) {
        unsigned short lodId = lodInfo->m_lodId;
        GfGameObj::ObjList& list = *GfGameObj::getList(2);
        for (GfGameObj::ObjList::iterator it = list.begin(); it != list.end(); ++it) {
            GfObjSetupMapLodAnim* setup =
                mm::mtl::rttiCast<GfObjSetupMapLodAnim>(GfObjManager::getObjInfo(*it)->m_setup);
            if (setup->m_lodId != lodId) {
                continue;
            }
            if (msg.m_lifts.size() == msg.m_lifts.capacity()) {
                // only the call of a stripped debug report is left
                mm::mtl::PtrSingleton<GfFieldLod>::get()->findBdatInfo(liftLod);
            } else {
                GF_OBJ_HANDLE* lift = *it;
                msg.m_lifts.push_back(lift);
            }
        }
    }
    msg.m_isLiftSwitch = static_cast<gmk::GmkElevator*>(gmk)->isLiftSwitch(static_cast<GfObj*>(m_owner)->m_handle);
}

GfComBehaviorGmk::GfComBehaviorGmk()
    : m_coliObject(nullptr), m_routeNavi(nullptr), m_menuContext(nullptr), m_bigObj(nullptr) {}

GfComBehaviorGmk::~GfComBehaviorGmk() {
    if (m_routeNavi != nullptr) {
        delete m_routeNavi;
        m_routeNavi = nullptr;
    }
}

void GfComBehaviorGmk::createMenuObj() {
    disposeMenuObj();
    GfObjSetupGimmick* setup =
        mm::mtl::rttiCast<GfObjSetupGimmick>(GfObjManager::getObjInfo(static_cast<GfObj*>(m_owner)->m_handle)->m_setup);
    if (!setup->pad_a1) {
        return;
    }
    GfMenuObjTargetInfo::OpenOtherParam param;
    param.m_obj = static_cast<GfObj*>(m_owner)->m_handle;
    param.m_nameBdat = GfDataBdat::getFP(0x1b0);
    if (!GfGameUtil::getNameMsId(param.m_nameId, static_cast<GfObj*>(m_owner)->m_handle)) {
        return;
    }
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
    if (gmk == nullptr || !gmk->isValid()) {
        return;
    }
    unsigned char* fp = gmk->getBindedBdatFp();
    int row = gmk->m_createInfo.m_bdatId;
    switch (gmk->getGmkType()) {
    case gmk::GmkCollection::TYPE:
        param.m_symbol = true;
        param.m_shopId = 2;
        if (GfGameManager::isGameTypeIra()) {
            param.m_pointId = (unsigned short)static_cast<gmk::GmkCollection*>(gmk)->getCategoryName_fld_gmkname();
            if (param.m_pointId != 0) {
                param.m_pointBdat = GfDataBdat::getFP(0x1b0);
                param.m_collect =
                    static_cast<const gmk::GmkCollection::BdatInfo*>(gmk->m_createInfo.m_bdatInfo)->m_collectionTable;
            }
        }
        break;
    case gmk::GmkSalvage::TYPE:
        param.m_symbol = true;
        param.m_shopId = 0;
        param.m_pointBdat = GfDataBdat::getFP(0x1bd);
        param.m_pointId = (unsigned short)Bdat::getValCheck(fp, "SalvagePointName", row, 2);
        break;
    case 0x24:
        param.m_symbol = true;
        param.m_shopId = 1;
        break;
    case 0x3a:
        param.m_nameBdat = GfDataBdat::getFP(0x1c1);
        break;
    case gmk::GmkCamp::TYPE:
        param.m_symbol = true;
        param.m_shopId = 0;
        param.m_pointBdat = GfDataBdat::getFP(0x1c2);
        param.m_pointId = (unsigned short)Bdat::getValCheck(fp, "CampPointName", row, 2);
        break;
    }
    int offsetId = GfGameUtil::getUiOffsetId(param.m_obj);
    param.m_offset.m_bone = nullptr;
    param.m_offset.m_offset = mm::Vec3::zero;
    GfMenuBdat::getMenuOffset(offsetId, param.m_offset);
    m_menuContext = GfMenuCallContext::create();
    GfMenuObjTargetInfo::openOther(m_menuContext, param);
}

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

void GfComBehaviorGmk::update(const fw::UpdateInfo& info) {
    mm::Vec3 velocity;
    if (m_routeNavi == nullptr) {
        velocity = mm::Vec3(0.0f, 0.0f, 0.0f);
    } else {
        fw::ReferenceFrame* frame = m_owner->getComponent<GfComTransform>(0)->getFrame().operator->();
        const mm::Vec3& pos = frame->getWorldTransform().position;
        gmk::GmkRouteNavi::UpdateInfo naviInfo;
        naviInfo.m_pos.x = pos.x;
        naviInfo.m_pos.y = pos.y;
        naviInfo.m_pos.z = pos.z;
        m_routeNavi->update(naviInfo);
        mm::Vec3 dir = m_routeNavi->pad_90 - pos;
        dir.normalize();
        velocity = dir * 2.0f;
    }
    if (m_coliObject != nullptr) {
        m_coliObject->setDir(velocity * info.m_deltaTime);
        if (m_routeNavi != nullptr) {
            fw::UpdatableObject* owner = m_owner;
            // only the call is left of the turn toward the route: the rotation it gives is not stored
            atan2f(velocity.x, velocity.z);
            owner->getComponent<GfComTransform>(0)->getFrame()->getWorldTransformForWrite();
        }
    }
    m_bigObj.update(info.m_deltaTime);
}

void GfComBehaviorGmk::setActivateCollison(bool activate) {
    if (fw::ColiMoveObject* coli = getColiObject()) {
        coli->setActivate(activate);
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

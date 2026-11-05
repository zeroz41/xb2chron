#include "classes/idcoli/IDColiObj.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/ColiManager.h"
#include "classes/fw/ColiObjUserData.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/ColiUserData.h"
#include "classes/fw/ColiObjUserData.h"
#include "idcoli/IDColiParms.h"
#include "classes/fw/ColiManager.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/WorkCpu.h"

namespace fw {

void ColiObject::setColiObject(idcoli::IDColiObj* coliObj) { m_coliObj = coliObj; }

void ColiObject::setHitMaterialFlag(unsigned int flag) {
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        parms.setOffMaterialBit(~flag);
    } else if (m_coliObj != nullptr && m_coliObj->m_type == 2) {
        idcoli::IDColiParmsPhantom parms(m_coliObj);
        parms.setOffMaterialBit(~flag);
    }
}

void ColiObject::setColiType(ColiType type) {
    m_followType = type;
    if (type == 0) {
        m_flags |= 1;
    }
}

void ColiObject::setPriority(int priority) {
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        parms.setPriority(priority);
    }
}

void ColiObject::setState(ColiState state) {
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        parms.setState(static_cast<idcoli::ColiState>(state));
    }
}

void ColiObject::clearState(ColiState state) {
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        parms.clearState(static_cast<idcoli::ColiState>(state));
    }
}

void ColiObject::resetCharacter(float height, float radius) {
    if (m_shape.get() != nullptr && m_shape.get()->m_kind == 3) {
        ColiShapeCharacter* shape = static_cast<ColiShapeCharacter*>(m_shape.get());
        shape->m_height = height;
        shape->m_radius = radius;
        if (isChar()) {
            idcoli::IDColiParmsCharacter parms(m_coliObj);
            parms.createCharacter(height, radius);
        } else if (m_coliObj != nullptr && m_coliObj->m_type == 2) {
            idcoli::IDColiParmsPhantom parms(m_coliObj);
            parms.createCharacter(height, radius);
        }
    }
}

const mm::Mat44& ReferenceFrame::getSyncedWorldMatrix() {
    if ((m_syncFlags & 4) == 0) {
        syncWorldTransform();
        const mm::Quat& q = m_worldTransform.rotation;
        const float x2 = q.x + q.x;
        const float y2 = q.y + q.y;
        const float z2 = q.z + q.z;
        const float xx = q.x * x2;
        const float xz = q.x * z2;
        const float yy = q.y * y2;
        const float xy = q.x * y2;
        const float wx = x2 * q.w;
        const float wy = y2 * q.w;
        const float wz = q.w * z2;
        const float zz = q.z * z2;
        const float yz = q.y * z2;
        m_worldMatrix.m[0][0] = 1.0f - (yy + zz);
        m_worldMatrix.m[0][1] = xy + wz;
        m_worldMatrix.m[0][2] = xz - wy;
        m_worldMatrix.m[0][3] = 0.0f;
        m_worldMatrix.m[1][0] = xy - wz;
        m_worldMatrix.m[1][1] = 1.0f - (xx + zz);
        m_worldMatrix.m[1][2] = yz + wx;
        m_worldMatrix.m[1][3] = 0.0f;
        m_worldMatrix.m[2][0] = xz + wy;
        m_worldMatrix.m[2][1] = yz - wx;
        m_worldMatrix.m[2][2] = 1.0f - (xx + yy);
        m_worldMatrix.m[2][3] = 0.0f;
        m_worldMatrix.m[3][0] = 0.0f;
        m_worldMatrix.m[3][1] = 0.0f;
        m_worldMatrix.m[3][2] = 0.0f;
        m_worldMatrix.m[3][3] = 1.0f;
        const mm::Vec3 pos = m_worldTransform.position;
        m_worldMatrix.m[3][0] = pos.x;
        m_worldMatrix.m[3][1] = pos.y;
        m_worldMatrix.m[3][2] = pos.z;
        m_syncFlags |= 4;
    }
    return m_worldMatrix;
}

ColiObject::ColiObject()
    : m_coliObj(nullptr), m_flags(0), pad_38(0), pad_40(nullptr), m_eventMask(0), m_listener(nullptr),
      m_userData(nullptr), m_scale(1.0f) {
    pad_60 = mm::Mat44::identity;
    m_matrix = mm::Mat44::identity;
}

ColiObject::~ColiObject() {
    if (m_coliObj != nullptr) {
        // the interface and the frame count are read and dropped (1.0.0's destructor does the same)
        mm::mtl::PtrSingleton<ColiManager>::get()->getInterface();
        ml::WorkCpu::getFrameCount();
        m_coliObj->release();
        m_coliObj = nullptr;
    }
    mm::mtl::PtrSingleton<ColiManager>::get()->removeObject(this);
}

void ColiObject::setHandle(unsigned int handle) {
    m_objUserData.m_handle = handle;
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        parms.setUserData(&m_objUserData);
    } else if (m_coliObj != nullptr && m_coliObj->m_type == 2) {
        idcoli::IDColiParmsPhantom parms(m_coliObj);
        parms.setUserData(&m_objUserData);
    }
}

bool ColiObject::isChar() const { return m_coliObj != nullptr && m_coliObj->m_type == 1; }

void ColiObject::setInstantlyMatrix(mm::Mat44 const& matrix) {
    float scale = m_scale;
    m_matrix = matrix;
    mm::Mat44 local(matrix);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            local.m[i][j] *= scale;
        }
    }
    local.mulCopy(pad_60, local);
    if (m_coliObj != nullptr) {
        switch (m_coliObj->m_type) {
        case 1: {
            idcoli::IDColiParmsCharacter parms(m_coliObj);
            parms.setInstantlyMatrix(local);
            break;
        }
        case 2: {
            idcoli::IDColiParmsPhantom parms(m_coliObj);
            parms.setInstantlyMatrix(local);
            break;
        }
        }
    }
}

void ColiObject::setMatrix(mm::Mat44 const& matrix) {
    float scale = m_scale;
    m_matrix = matrix;
    mm::Mat44 local(matrix);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            local.m[i][j] *= scale;
        }
    }
    local.mulCopy(pad_60, local);
    if (m_coliObj != nullptr) {
        switch (m_coliObj->m_type) {
        case 1: {
            idcoli::IDColiParmsCharacter parms(m_coliObj);
            parms.setMatrix(local);
            break;
        }
        case 2: {
            idcoli::IDColiParmsPhantom parms(m_coliObj);
            parms.setMatrix(local);
            break;
        }
        }
    }
}

const mm::Mat44& ColiObject::getMatrix() const { return m_matrix; }

int ColiObject::getPriority() const {
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        return parms.getPriority();
    }
    return 0;
}

bool ColiObject::isGrand() const { return m_coliObj != nullptr && m_coliObj->m_type == 3; }

bool ColiObject::testAttribute(ColiAtrr attribute) const {
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        return parms.isAttr(static_cast<idcoli::ColiAtrr>(attribute));
    }
    return false;
}

bool ColiObject::testState(ColiState state) const {
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        return parms.isState(static_cast<idcoli::ColiState>(state));
    }
    return false;
}

void ColiObject::setActivate(bool activate) {
    if (activate) {
        clearState(COLI_STATE_INACTIVE);
    } else {
        setState(COLI_STATE_INACTIVE);
    }
}

bool ColiObject::isActivate() const { return !testState(COLI_STATE_INACTIVE); }

unsigned int ColiObject::getHitMaterialFlag() const {
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        return ~parms.getOffMaterialBit();
    } else if (m_coliObj != nullptr && m_coliObj->m_type == 2) {
        idcoli::IDColiParmsPhantom parms(m_coliObj);
        return ~parms.getOffMaterialBit();
    }
    return 0;
}

void ColiObject::setAdsorption(float adsorption) {
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        parms.setAdsorption(adsorption);
    }
}

float ColiObject::getAdsorption() const {
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        return parms.getAdsorption();
    }
    return 0.0f;
}

bool ColiObject::isLanding() const {
    if (isChar()) {
        return m_coliObj->m_attr & 1;
    }
    return false;
}

bool ColiObject::isContactWall() const {
    if (isChar()) {
        return (m_coliObj->m_attr >> 2) & 1;
    }
    return false;
}

bool ColiObject::getAABB(mm::Vec3& min, mm::Vec3& max) const {
    if (isChar()) {
        idcoli::IDColiParmsCharacter parms(m_coliObj);
        min = parms.getMin();
        max = parms.getMax();
        return true;
    } else if (m_coliObj != nullptr && m_coliObj->m_type == 2) {
        idcoli::IDColiParmsPhantom parms(m_coliObj);
        min = parms.getMin();
        max = parms.getMax();
        return true;
    }
    return false;
}

void ColiObject::contact(IColiEventListener::EnterInfo const& info) {
    if (m_listener != nullptr && (m_eventMask & 2)) {
        m_listener->contact(info);
    }
}

void ColiObject::update() {}

void ColiObject::postUpdate() {
    if ((m_followType != 0 || (m_flags & 1)) && m_frame.get() != nullptr && m_coliObj != nullptr) {
        m_flags &= ~1;
        setMatrix(m_frame->getSyncedWorldMatrix());
    }
}

mm::mtl::RTTI ColiObject::m_rtti("ColiObject", nullptr, nullptr);
mm::mtl::RTTI ColiObjUserData::m_rtti("ColiObjUserData", &ColiUserData::m_rtti, nullptr);

}  // namespace fw

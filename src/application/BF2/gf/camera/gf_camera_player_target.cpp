#include "mm/mtl/FixStr.h"
#include "mm/mtl/Map.h"
#include "fw/PadRelay.h"
#include "classes/fw/CameraTarget.h"
#include "classes/gf/PlayerCameraTarget.h"
#include "gf/CameraPadData.h"
#include "gf/FileStaticVec3.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGamePlayerCamera.h"

namespace gf {

CameraPadData::CameraPadData() {
    reset();
    bind();
}

void CameraPadData::bind() {
    PadRelay::bind(0, 2, getAllocator(ALLOCATOR(0)));
    bindAction("reset", this, &CameraPadData::resetAction);
    bindAction("zoom", this, &CameraPadData::zoomCamera);
    bindAction("height", this, &CameraPadData::heightCamera);
    bindAction("side_left", this, &CameraPadData::sideLeftCamera);
    bindAction("side_right", this, &CameraPadData::sideRightCamera);
    bindAction("side_reset", this, &CameraPadData::sideResetCamera);
    bindAction("all_reset", this, &CameraPadData::allResetAction);
    bindAxis("arx", this, &CameraPadData::setARX);
    bindAxis("ary", this, &CameraPadData::setARY);
}

CameraPadData::~CameraPadData() {
    unbind();
}

void CameraPadData::update() {
    reset();
    PadRelay::update();
}

void CameraPadData::resetAction() {
    m_reset = true;
}

void CameraPadData::zoomCamera() {
    m_zoom = true;
}

void CameraPadData::heightCamera() {
    m_height = true;
}

void CameraPadData::sideLeftCamera() {
    m_sideLeft = true;
}

void CameraPadData::sideRightCamera() {
    m_sideRight = true;
}

void CameraPadData::sideResetCamera() {
    m_sideReset = true;
}

void CameraPadData::allResetAction() {
    m_allReset = true;
}

void CameraPadData::setARX(float value) {
    m_arx = value;
}

void CameraPadData::setARY(float value) {
    m_ary = value;
}

mm::mtl::RTTI PlayerCameraTarget::m_rtti("PlayerCameraTarget", &fw::CameraTarget::m_rtti, nullptr);

PlayerCameraTarget* PlayerCameraTarget::create() {
#line 35
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PlayerCameraTarget();
}

PlayerCameraTarget::PlayerCameraTarget()
    : m_position(mm::Vec3::zero), m_rotation(mm::Quat::identity), m_isState3(false), m_isStillState4(false),
      m_isState1(false), m_hasLink(false), m_hasGround(false), m_isRiding(false), m_inWater(false),
      m_groundHeight(0.0f), m_surfaceHeight(0.0f), m_up(mm::Vec3::unitY), m_front(mm::Vec3::unitZ),
      m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_partyMemberOK(true), m_requestReset(false) {
    writeTargetInfo();
    GfEvent::addEventCallback(this);
}

PlayerCameraTarget::~PlayerCameraTarget() {
    GfEvent::removeEventCallback(this);
}

void PlayerCameraTarget::update(const fw::UpdateInfo&) {
    writeTargetInfo();
    if (m_requestReset) {
        GfGamePlayerCamera::resetCamera();
        m_requestReset = false;
    }
}

void PlayerCameraTarget::requestResetCamera() {
    m_requestReset = true;
}

void PlayerCameraTarget::gevPartyMemberOK(bool ok) {
    m_partyMemberOK = ok;
}

}  // namespace gf

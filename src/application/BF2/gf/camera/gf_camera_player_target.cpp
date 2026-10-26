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

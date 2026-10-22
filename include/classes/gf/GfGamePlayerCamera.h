#ifndef CLASSES_GF_GFGAMEPLAYERCAMERA_H
#define CLASSES_GF_GFGAMEPLAYERCAMERA_H

#include "classes/fw/Camera.h"
#include "classes/fw/MessageObject.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/IGfEvent.h"
#include "classes/gf/PlayerCamera.h"
#include "classes/gf/PlayerCameraTarget.h"
#include "classes/mm/mtl/PtrSingleton.h"
namespace gf { class MsgPcResetCamera; }
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/RTTI.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGamePlayerCamera; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B55430: the player camera and the target it follows, created once the party is ready
class GfGamePlayerCamera : public ::mm::mtl::PtrSingleton< ::gf::GfGamePlayerCamera>, public ::gf::IGfEvent, public ::fw::MessageObject {
public:
    // out of line in 1.0.0; inline in 3.0.1
    GfGamePlayerCamera() {}
    virtual ~GfGamePlayerCamera();  // slot 0
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevPartyMemberOK(bool);  // slot 3
    static void build(const GfSetupParam& param);
    // out of line in 1.0.0; inline in 3.0.1
    void setup() {
        GfEvent::addEventCallback(this);
    }
    static void destroy();
    void cleanup();
    static void resetCameraForSceneJump();
    static void resetCamera();
    static void requestResetCamera();
    static void resetCameraClimb(ResetCameraWallTiming timing);
    static void resetCameraLoad();
    static void resetCameraBattleWarp();
    static void setTargetObject(GF_OBJ_HANDLE* handle);
    static bool isManualCamera();
    static float getSaveYaw();
    static float getSavePitch();
    static float getSaveDistance();
    static float getSaveHeight();
    static bool getSaveSide();
    static bool isSaveFreeMode();
    // out of line in 1.0.0; inline in 3.0.1
    void procMsgPcResetCamera(fw::MessageObject* sender, MsgPcResetCamera& msg) {
        if (PlayerCamera* camera = getPlayerCamera()) {
            camera->reset();
        }
    }
    // the singleton's camera as a PlayerCamera, none when there is no singleton, no camera or another kind
    // (inline: the name is not the original's)
    static PlayerCamera* getPlayerCamera() {
        GfGamePlayerCamera* self = get();
        if (self == nullptr) {
            return nullptr;
        }
        fw::Camera* camera = self->m_camera.get();
        if (camera == nullptr) {
            return nullptr;
        }
        return mm::mtl::rttiCast<PlayerCamera>(camera);
    }

    mm::mtl::IntrusivePtr<fw::Camera> m_camera;  // PlayerCamera::create's, on the camera manager's first layer; the name is not the original's
    mm::mtl::IntrusivePtr<PlayerCameraTarget> m_target;  // PlayerCameraTarget::create's, the camera manager's target; the name is not the original's
};
}  // namespace gf

#endif

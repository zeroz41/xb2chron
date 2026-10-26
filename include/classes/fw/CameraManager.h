#ifndef CLASSES_FW_CAMERAMANAGER_H
#define CLASSES_FW_CAMERAMANAGER_H

#include "classes/fw/CameraLayer.h"
#include "classes/fw/CameraTarget.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace ml { class Scn; }

namespace fw {
// table 0x7100B416D0; its base at 0x10 is its singleton (the destructor stores PtrSingleton<fw::CameraManager>'s
// table there and clears its instance)
class CameraManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::CameraManager> {
public:
    // table 0x7100B41768: the standby-logout listener the manager holds (at 0x370), with its manager behind it
    class Listener {
    public:
        Listener(CameraManager* owner) : m_owner(owner) {}
        virtual void onWkStandbyLogout();  // slot 0
        CameraManager* m_owner;  // the name is not the original's
    };
    // createManager makes it on the framework's scene: each layer is set up on it with its index
    CameraManager(ml::Scn* scn);
    virtual ~CameraManager();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 8

    unsigned char pad_18[0x8];
    // the four layers the destructor cleans up: GfDeadCamera pushes onto the first, GfGameCamera a sub view camera
    // onto each of the others (the one its gf::VIEWCAM names)
    CameraLayer m_layers[4];
    // what the cameras follow: GfGamePlayerCamera hands it its PlayerCameraTarget and clears it again; the name is
    // not the original's
    mm::mtl::IntrusivePtr<CameraTarget> m_target;
    // the listener's onWkStandbyLogout clears it (as GfComIK's viewer listener does its m_pViewer; the name is not
    // the original's)
    void* m_pViewer;
    Listener m_listener;  // the name is not the original's
};
}  // namespace fw

#endif

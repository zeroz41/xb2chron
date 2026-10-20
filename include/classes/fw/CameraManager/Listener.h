#ifndef CLASSES_FW_CAMERAMANAGER_LISTENER_H
#define CLASSES_FW_CAMERAMANAGER_LISTENER_H

#include "classes/fw/CameraManager.h"

namespace fw {
// table 0x7100B41768
class CameraManager::Listener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace fw

#endif

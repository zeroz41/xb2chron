#ifndef CLASSES_FW_CAMERAMANAGER_H
#define CLASSES_FW_CAMERAMANAGER_H

#include "classes/fw/CameraLayer.h"
#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B416D0; its base at 0x10 is its singleton (the destructor stores PtrSingleton<fw::CameraManager>'s
// table there and clears its instance)
class CameraManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::CameraManager> {
public:
    class Listener;
    virtual ~CameraManager();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 8

    unsigned char pad_18[0x8];
    CameraLayer m_layer;  // the first of the four layers the destructor cleans up; GfDeadCamera pushes onto it
};
}  // namespace fw

#endif

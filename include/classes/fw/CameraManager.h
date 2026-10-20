#ifndef CLASSES_FW_CAMERAMANAGER_H
#define CLASSES_FW_CAMERAMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a base of fw::CameraManager no evidence names yet
class TUnk_B41728 {
public:
    virtual ~TUnk_B41728();
};
// table 0x7100B416D0; base at 0x10 unknown (TUnk_B41728)
class CameraManager : public ::fw::ManagerObject, public TUnk_B41728 {
public:
    class Listener;
    virtual ~CameraManager();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 8
};
}  // namespace fw

#endif

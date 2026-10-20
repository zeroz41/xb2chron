#ifndef CLASSES_GF_SCRIPTCAMERAENTITY_H
#define CLASSES_GF_SCRIPTCAMERAENTITY_H

#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B45F10
class ScriptCameraEntity : public ::fw::Camera {
public:
    virtual ~ScriptCameraEntity();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void getName() const;  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
};
}  // namespace gf

#endif

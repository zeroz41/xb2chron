#ifndef CLASSES_FW_LIGHTMANAGER_H
#define CLASSES_FW_LIGHTMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a base of fw::LightManager no evidence names yet
class TUnk_B41838 {
public:
    virtual ~TUnk_B41838();
};
// table 0x7100B417E0; base at 0x10 unknown (TUnk_B41838)
class LightManager : public ::fw::ManagerObject, public TUnk_B41838 {
public:
    virtual ~LightManager();  // slot 0
    virtual void update(fw::UpdateInfo const&, unsigned int) {}  // slot 8
};
}  // namespace fw

#endif

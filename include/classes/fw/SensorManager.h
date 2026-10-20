#ifndef CLASSES_FW_SENSORMANAGER_H
#define CLASSES_FW_SENSORMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a base of fw::SensorManager no evidence names yet
class TUnk_B42D10 {
public:
    virtual ~TUnk_B42D10();
};
// table 0x7100B42CB8; base at 0x10 unknown (TUnk_B42D10)
class SensorManager : public ::fw::ManagerObject, public TUnk_B42D10 {
public:
    virtual ~SensorManager();  // slot 0
    virtual void getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
};
}  // namespace fw

#endif

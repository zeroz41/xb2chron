#ifndef CLASSES_GF_GFCOMENVSENSOR_ENVLISTENER_H
#define CLASSES_GF_GFCOMENVSENSOR_ENVLISTENER_H

#include "classes/gf/GfComEnvSensor.h"

namespace gf {
// table 0x7100B66140
class GfComEnvSensor::EnvListener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace gf

#endif

#ifndef CLASSES_EVENT_CAMINTERFACE_H
#define CLASSES_EVENT_CAMINTERFACE_H

#include "classes/fw/Camera.h"

namespace event {
// table 0x7100B3C778
class CamInterface : public ::fw::Camera {
public:
    virtual ~CamInterface();  // slot 0
};
}  // namespace event

#endif

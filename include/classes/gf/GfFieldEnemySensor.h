#ifndef CLASSES_GF_GFFIELDENEMYSENSOR_H
#define CLASSES_GF_GFFIELDENEMYSENSOR_H

#include "classes/fw/IColiEventListener.h"

namespace gf {
// table 0x7100B65DE8
class GfFieldEnemySensor : public ::fw::IColiEventListener {
public:
    virtual void enter(fw::IColiEventListener::EnterInfo const&);  // slot 0
    virtual void leave(fw::IColiEventListener::LeaveInfo const&);  // slot 1
};
}  // namespace gf

#endif

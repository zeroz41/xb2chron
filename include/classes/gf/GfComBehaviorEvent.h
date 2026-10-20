#ifndef CLASSES_GF_GFCOMBEHAVIOREVENT_H
#define CLASSES_GF_GFCOMBEHAVIOREVENT_H

#include "classes/gf/GfComBehavior.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B66158
class GfComBehaviorEvent : public ::gf::GfComBehavior {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComBehaviorEvent();  // slot 1
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
};
}  // namespace gf

#endif

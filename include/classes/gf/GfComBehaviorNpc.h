#ifndef CLASSES_GF_GFCOMBEHAVIORNPC_H
#define CLASSES_GF_GFCOMBEHAVIORNPC_H

#include "classes/gf/GfComBehavior.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B66840
class GfComBehaviorNpc : public ::gf::GfComBehavior {
public:
    class Listener;
    class LocalSteerIsTargetNotPlayer;
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComBehaviorNpc();  // slot 1
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    virtual void getComAsm() const;  // slot 7
};
}  // namespace gf

#endif

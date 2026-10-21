#ifndef CLASSES_GF_GFCOMBEHAVIORMOB_H
#define CLASSES_GF_GFCOMBEHAVIORMOB_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComBehavior.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B66500
class GfComBehaviorMob : public ::gf::GfComBehavior {
public:
    class Listener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorMob();  // slot 1
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    virtual void getPos() const;  // slot 7
    virtual void getRot() const;  // slot 8
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif

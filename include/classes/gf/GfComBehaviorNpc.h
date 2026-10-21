#ifndef CLASSES_GF_GFCOMBEHAVIORNPC_H
#define CLASSES_GF_GFCOMBEHAVIORNPC_H

#include "mm/mtl/RTTI.h"
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
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorNpc();  // slot 1
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    virtual void getComAsm() const;  // slot 7
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif

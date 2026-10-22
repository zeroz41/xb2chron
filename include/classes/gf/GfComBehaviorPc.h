#ifndef CLASSES_GF_GFCOMBEHAVIORPC_H
#define CLASSES_GF_GFCOMBEHAVIORPC_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComBehavior.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class CallBackCache; }
namespace gf { class GfComAsm; }

namespace gf {
// table 0x7100B693E8
class GfComBehaviorPc : public ::gf::GfComBehavior {
public:
    class Listener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorPc();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    virtual void procAnimCallback(gf::GfComAsm*, gf::CallBackCache const&);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif

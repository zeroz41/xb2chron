#ifndef CLASSES_GF_GFCOMBEHAVIOREXTRA_H
#define CLASSES_GF_GFCOMBEHAVIOREXTRA_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/Vector.h"
#include "classes/gf/GfComBehavior.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class MsgObjectNotifyAsmCallback; }

namespace gf {
// table 0x7100B661D8
class GfComBehaviorExtra : public ::gf::GfComBehavior {
public:
    GfComBehaviorExtra();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorExtra();  // slot 1
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 5
    void procMsgObjectNotifyAsmCallback(fw::MessageObject* sender, MsgObjectNotifyAsmCallback& msg);
    void setup();
    void cleanup();
    static mm::mtl::RTTI m_rtti;

    // the "attachmentTrans" annotations' commands, executed on the asm component by the next update (the name is
    // not the original's)
    mm::mtl::Vector<const char*> m_commands;
};
}  // namespace gf

#endif

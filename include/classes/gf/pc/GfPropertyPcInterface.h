#ifndef CLASSES_GF_PC_GFPROPERTYPCINTERFACE_H
#define CLASSES_GF_PC_GFPROPERTYPCINTERFACE_H

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table none (its derived classes')
class GfPropertyPcInterface {
public:
    virtual void setup(gf::GfComPropertyPc const&) = 0;  // slot 0
    virtual void cleanup(gf::GfComPropertyPc const&) = 0;  // slot 1
    virtual void flush(gf::GfComPropertyPc const&) = 0;  // slot 2
    virtual void flushOwner(gf::GfComPropertyPc&) {}  // slot 3
    // slot 4: inline, emitted with GfPropertyBattle's table (returns false)
    virtual bool recieveMessage(gf::GfComPropertyPc const&, fw::MessageObject*, fw::Message&) { return false; }
};
}}  // namespace gf::pc

#endif

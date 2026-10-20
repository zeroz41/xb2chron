#ifndef CLASSES_GF_PC_GFPROPERTYFIELD_H
#define CLASSES_GF_PC_GFPROPERTYFIELD_H

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B67E78
class GfPropertyField {
public:
    virtual void setup(gf::GfComPropertyPc const&);  // slot 0
    virtual void cleanup(gf::GfComPropertyPc const&);  // slot 1
    virtual void flush(gf::GfComPropertyPc const&);  // slot 2
    virtual void flushOwner(gf::GfComPropertyPc&);  // slot 3
    virtual void recieveMessage(gf::GfComPropertyPc const&, fw::MessageObject*, fw::Message&);  // slot 4
};
}}  // namespace gf::pc

#endif

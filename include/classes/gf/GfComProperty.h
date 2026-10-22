#ifndef CLASSES_GF_GFCOMPROPERTY_H
#define CLASSES_GF_GFCOMPROPERTY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B69C30
class GfComProperty : public ::gf::GfComponent {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComProperty();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int) {}  // slot 3
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_10[0x28];  // fields: its constructor zeroes 0x10-0x38
};
}  // namespace gf

#endif

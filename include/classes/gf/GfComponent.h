#ifndef CLASSES_GF_GFCOMPONENT_H
#define CLASSES_GF_GFCOMPONENT_H

#include "mm/mtl/RTTI.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table none (its derived classes')
class GfComponent {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;  // slot 0
    virtual ~GfComponent();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int) = 0;  // slot 3
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    unsigned char pad_8[0x8];  // fields: size from its derived classes
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFCOMPONENT_H
#define CLASSES_GF_GFCOMPONENT_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/ComponentObject.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table none (its derived classes')
class GfComponent : public ::fw::ComponentObject {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;  // slot 0
    virtual ~GfComponent() {}  // slot 1: inline (no symbol; a derived destructor calls none)
    virtual void changeLayer(unsigned int, unsigned int) = 0;  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    static mm::mtl::RTTI m_rtti;  // the base every component's m_rtti names (defined by GfObjAcc's unit)
};
}  // namespace gf

#endif

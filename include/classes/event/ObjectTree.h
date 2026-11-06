#ifndef CLASSES_EVENT_OBJECTTREE_H
#define CLASSES_EVENT_OBJECTTREE_H

#include "classes/event/Object.h"

namespace event {
// table 0x7100B3DCB0
class ObjectTree : public ::event::Object {
public:
    // inline (ObjectList's constructor builds its root and category objects with it); type 1
    ObjectTree(const char* name) : Object(static_cast<OBJTYPE>(1), name) {}
    virtual ~ObjectTree();  // slot 0
};
}  // namespace event

#endif

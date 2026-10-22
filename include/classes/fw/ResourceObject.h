#ifndef CLASSES_FW_RESOURCEOBJECT_H
#define CLASSES_FW_RESOURCEOBJECT_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace fw {
// the priority a resource loads with (fw::SoundResource::request takes one; GfEvtSe::createSe passes 10)
enum LOAD_PRIO : int;

// table 0x7100B42B18; counted: its constructor zeroes the count at 8 before it stores its table (the base's inline
// constructor), SoundResource::request adds a reference through it, and GfEvtSe releases one with
// reference_object.h's assertion and slot 1
class ResourceObject : public ::mm::mtl::ReferenceObject {
public:
    virtual ~ResourceObject();  // slot 0
    virtual void update() = 0;  // slot 2
    // whether it has loaded (GfEvtSe::isLoadedSe waits for every SE's)
    virtual bool valid() const = 0;  // slot 3
};
}  // namespace fw

#endif

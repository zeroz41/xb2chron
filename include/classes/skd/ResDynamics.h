#ifndef CLASSES_SKD_RESDYNAMICS_H
#define CLASSES_SKD_RESDYNAMICS_H

#include "classes/anm/ReferenceObject.h"

namespace skd {
// table 0x7100B81628; a dynamics resource in place in its binary (DynamicsImporter::import gives it its table);
// its destructor adds nothing to anm::ReferenceObject's (slot 0 is that one)
class ResDynamics : public anm::ReferenceObject {
public:
    virtual ~ResDynamics() {}  // slot 0
};
}  // namespace skd

#endif

#ifndef CLASSES_GF_GFOBJSETUPEVENTOBJ_H
#define CLASSES_GF_GFOBJSETUPEVENTOBJ_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A7C8
class GfObjSetupEventObj : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupEventObj();  // slot 1
};
}  // namespace gf

#endif

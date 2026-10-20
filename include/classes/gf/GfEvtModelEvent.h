#ifndef CLASSES_GF_GFEVTMODELEVENT_H
#define CLASSES_GF_GFEVTMODELEVENT_H

#include "classes/gf/GfEvtModel.h"

namespace gf {
// table 0x7100B54048
class GfEvtModelEvent : public ::gf::GfEvtModel {
public:
    virtual ~GfEvtModelEvent();  // slot 0
    virtual void getRTTI() const;  // slot 2
};
}  // namespace gf

#endif

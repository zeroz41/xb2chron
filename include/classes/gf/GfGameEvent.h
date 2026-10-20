#ifndef CLASSES_GF_GFGAMEEVENT_H
#define CLASSES_GF_GFGAMEEVENT_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameEvent; }

namespace gf {
// table 0x7100B54448
class GfGameEvent : public ::mm::mtl::PtrSingleton< ::gf::GfGameEvent> {
public:
    virtual ~GfGameEvent();  // slot 0
};
}  // namespace gf

#endif

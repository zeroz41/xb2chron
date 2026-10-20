#ifndef CLASSES_GF_GFQUESTEVENT_H
#define CLASSES_GF_GFQUESTEVENT_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfQuestEvent; }

namespace gf {
// table 0x7100B56D70
class GfQuestEvent : public ::mm::mtl::PtrSingleton< ::gf::GfQuestEvent> {
public:
    virtual ~GfQuestEvent();  // slot 0
};
}  // namespace gf

#endif

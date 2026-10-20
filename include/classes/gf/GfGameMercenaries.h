#ifndef CLASSES_GF_GFGAMEMERCENARIES_H
#define CLASSES_GF_GFGAMEMERCENARIES_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameMercenaries; }

namespace gf {
// table 0x7100B56D30
class GfGameMercenaries : public ::mm::mtl::PtrSingleton< ::gf::GfGameMercenaries> {
public:
    virtual ~GfGameMercenaries();  // slot 0
};
}  // namespace gf

#endif

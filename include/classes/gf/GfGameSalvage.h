#ifndef CLASSES_GF_GFGAMESALVAGE_H
#define CLASSES_GF_GFGAMESALVAGE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameSalvage; }

namespace gf {
// table 0x7100B56ED8
class GfGameSalvage : public ::mm::mtl::PtrSingleton< ::gf::GfGameSalvage> {
public:
    virtual ~GfGameSalvage();  // slot 0
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFTRINITYATTACK_H
#define CLASSES_GF_GFTRINITYATTACK_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfTrinityAttack; }

namespace gf {
// table 0x7100B56AB0
class GfTrinityAttack : public ::mm::mtl::PtrSingleton< ::gf::GfTrinityAttack> {
public:
    virtual ~GfTrinityAttack();  // slot 0
};
}  // namespace gf

#endif

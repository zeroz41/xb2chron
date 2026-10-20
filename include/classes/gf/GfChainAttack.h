#ifndef CLASSES_GF_GFCHAINATTACK_H
#define CLASSES_GF_GFCHAINATTACK_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfChainAttack; }

namespace gf {
// table 0x7100B54718
class GfChainAttack : public ::mm::mtl::PtrSingleton< ::gf::GfChainAttack> {
public:
    virtual ~GfChainAttack();  // slot 0
};
}  // namespace gf

#endif

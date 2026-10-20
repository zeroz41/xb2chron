#ifndef CLASSES_GF_GFSLOWATTACK_H
#define CLASSES_GF_GFSLOWATTACK_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSlowAttack; }

namespace gf {
// table 0x7100B55FB0
class GfSlowAttack : public ::mm::mtl::PtrSingleton< ::gf::GfSlowAttack> {
public:
    virtual ~GfSlowAttack();  // slot 0
};
}  // namespace gf

#endif

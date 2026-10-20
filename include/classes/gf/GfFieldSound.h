#ifndef CLASSES_GF_GFFIELDSOUND_H
#define CLASSES_GF_GFFIELDSOUND_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldSound; }

namespace gf {
// table 0x7100B525B8
class GfFieldSound : public ::mm::mtl::PtrSingleton< ::gf::GfFieldSound> {
public:
    virtual ~GfFieldSound();  // slot 0
};
}  // namespace gf

#endif

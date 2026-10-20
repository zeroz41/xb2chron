#ifndef CLASSES_GF_GFGAMEPLAYERFORMATION_H
#define CLASSES_GF_GFGAMEPLAYERFORMATION_H

#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGamePlayerFormation; }

namespace gf {
// table 0x7100B558C0
class GfGamePlayerFormation : public ::mm::mtl::PtrSingleton< ::gf::GfGamePlayerFormation>, public ::fw::MessageObject {
public:
    virtual ~GfGamePlayerFormation();  // slot 0
};
}  // namespace gf

#endif

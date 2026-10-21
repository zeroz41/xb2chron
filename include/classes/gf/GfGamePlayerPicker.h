#ifndef CLASSES_GF_GFGAMEPLAYERPICKER_H
#define CLASSES_GF_GFGAMEPLAYERPICKER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf {
// no table left in the module; its singleton's instance is the .bss its unit owns, between the player camera's and
// the unique scheduler's (each unit there owns its class's), reached through the GOT as theirs are
class GfGamePlayerPicker : public ::mm::mtl::PtrSingleton< ::gf::GfGamePlayerPicker> {
public:
    static bool isPick();
    unsigned char pad_8[0x1C];
    unsigned char m_pick;  // nonzero while picking (isPick)
};
}  // namespace gf

#endif

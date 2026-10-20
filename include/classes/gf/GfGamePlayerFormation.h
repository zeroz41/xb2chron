#ifndef CLASSES_GF_GFGAMEPLAYERFORMATION_H
#define CLASSES_GF_GFGAMEPLAYERFORMATION_H

#include "classes/fw/MessageObject.h"

namespace gf {
// a base of gf::GfGamePlayerFormation no evidence names yet
class TUnk_B558C0 {
public:
    virtual ~TUnk_B558C0();
};
// table 0x7100B558C0; base at 0x0 unknown (TUnk_B558C0)
class GfGamePlayerFormation : public TUnk_B558C0, public ::fw::MessageObject {
public:
    virtual ~GfGamePlayerFormation();  // slot 0
};
}  // namespace gf

#endif

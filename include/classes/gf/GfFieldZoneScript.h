#ifndef CLASSES_GF_GFFIELDZONESCRIPT_H
#define CLASSES_GF_GFFIELDZONESCRIPT_H

#include "classes/gf/IEventZone.h"

namespace gf {
// a base of gf::GfFieldZoneScript no evidence names yet
class TUnk_B527F0 {
public:
    virtual ~TUnk_B527F0();
};
// table 0x7100B527F0; base at 0x0 unknown (TUnk_B527F0)
class GfFieldZoneScript : public TUnk_B527F0, public ::gf::IEventZone {
public:
    virtual ~GfFieldZoneScript();  // slot 0
};
}  // namespace gf

#endif

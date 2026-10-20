#ifndef CLASSES_GF_GFBDATUNIQUEMOTION_H
#define CLASSES_GF_GFBDATUNIQUEMOTION_H

#include "classes/fw/MessageObject.h"

namespace gf {
// a base of gf::GfBdatUniqueMotion no evidence names yet
class TUnk_B47F28 {
public:
    virtual ~TUnk_B47F28();
    virtual void bdatRefresh() = 0;
};
// a base of gf::GfBdatUniqueMotion no evidence names yet
class TUnk_B47F50 {
public:
    virtual ~TUnk_B47F50();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B47F28; base at 0x0 unknown (TUnk_B47F28), base at 0x8 unknown (TUnk_B47F50)
class GfBdatUniqueMotion : public TUnk_B47F28, public TUnk_B47F50, public ::fw::MessageObject {
public:
    virtual ~GfBdatUniqueMotion();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif

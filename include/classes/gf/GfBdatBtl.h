#ifndef CLASSES_GF_GFBDATBTL_H
#define CLASSES_GF_GFBDATBTL_H

#include "classes/gf/_gfbbt.h"

namespace gf {
// a base of gf::GfBdatBtl no evidence names yet
class TUnk_B462F8 {
public:
    virtual ~TUnk_B462F8();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B462F8; base at 0x0 unknown (TUnk_B462F8)
class GfBdatBtl : public TUnk_B462F8, public ::gf::_gfbbt {
public:
    virtual ~GfBdatBtl();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif

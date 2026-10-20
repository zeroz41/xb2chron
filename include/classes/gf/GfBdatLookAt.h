#ifndef CLASSES_GF_GFBDATLOOKAT_H
#define CLASSES_GF_GFBDATLOOKAT_H

#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatLookAt; }

namespace gf {
// a base of gf::GfBdatLookAt no evidence names yet
class TUnk_B46FD0 {
public:
    virtual ~TUnk_B46FD0();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B46FA8; base at 0x8 unknown (TUnk_B46FD0)
class GfBdatLookAt : public ::mm::mtl::PtrSingleton< ::gf::GfBdatLookAt>, public TUnk_B46FD0, public ::fw::MessageObject {
public:
    virtual ~GfBdatLookAt();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif

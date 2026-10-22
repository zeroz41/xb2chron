#ifndef CLASSES_EVENT_OBJECTPARTYLIST_H
#define CLASSES_EVENT_OBJECTPARTYLIST_H

#include "mm/mtl/FixedVector.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3FD48
class ObjectPartyList {
public:
    virtual ~ObjectPartyList();  // slot 0
    static mm::mtl::FixedVector<gf::GF_OBJ_HANDLE*, 3> s_drlist;
    static mm::mtl::FixedVector<gf::GF_OBJ_HANDLE*, 3> s_bllist;
};
}  // namespace event

#endif

#ifndef CLASSES_EVENT_OBJECTPARTYLIST_H
#define CLASSES_EVENT_OBJECTPARTYLIST_H

#include "mm/mtl/FixedVector.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3FD48
class ObjectPartyList {
public:
    // inline and empty: Singleton<ObjectPartyList>::getPtr (evt_status.getLeader) only stores the table and
    // registers no destructor
    // user-provided, so getPtr stores the table at run time (evt_status.getLeader) instead of constant-initializing
    ObjectPartyList() {}
    virtual ~ObjectPartyList() {}  // slot 0
    unsigned int getLeaderDriverId() const;
    static mm::mtl::FixedVector<gf::GF_OBJ_HANDLE*, 3> s_drlist;
    static mm::mtl::FixedVector<gf::GF_OBJ_HANDLE*, 3> s_bllist;
};
}  // namespace event

#endif

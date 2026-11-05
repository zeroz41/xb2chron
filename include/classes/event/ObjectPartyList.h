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
    // 0x710011E378 (ObjectManager::OnEventProc's message 4 tail-calls it)
    void init();
    // the id-th (from 1) party driver (blade) handle, -1 for 0 or past the end (ObjectList::getDriverByBlade and
    // the ObjectList creators inline them; the names are not the original's)
    gf::GF_OBJ_HANDLE* getDriver(unsigned int id) const {
        if (id == 0 || id > s_drlist.size()) {
            return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
        return s_drlist[id - 1];
    }
    gf::GF_OBJ_HANDLE* getBlade(unsigned int id) const {
        if (id == 0 || id > s_bllist.size()) {
            return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
        return s_bllist[id - 1];
    }
    static mm::mtl::FixedVector<gf::GF_OBJ_HANDLE*, 3> s_drlist;
    static mm::mtl::FixedVector<gf::GF_OBJ_HANDLE*, 3> s_bllist;
};
}  // namespace event

#endif

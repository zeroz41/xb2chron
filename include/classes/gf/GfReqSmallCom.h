#ifndef CLASSES_GF_GFREQSMALLCOM_H
#define CLASSES_GF_GFREQSMALLCOM_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedList.h"

namespace gf { class GfReqSmallCom; class SCOM; class GF_SCOM_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AF20; GfReqManager makes one (0x1B078 bytes, 3.0.1's new) and updates it after its own commands
class GfReqSmallCom : public ::mm::mtl::PtrSingleton< ::gf::GfReqSmallCom> {
public:
    typedef mm::mtl::FixedList<SCOM*, 2048> RequestList;

    GfReqSmallCom();
    virtual ~GfReqSmallCom();  // slot 0
    void update(const fw::UpdateInfo& info);
    static bool isExistCommand();
    bool isValid(GF_SCOM_HANDLE* handle);  // the request is still queued or running

    // inline: the create functions queue their request in place, then return its handle
    static unsigned long addRequest(SCOM* request);
    static unsigned long addRequestParallel(SCOM* request);
    // a new request's handle: the next count, never -1 (the name is not the original's)
    unsigned long newHandle() {
        unsigned long handle = m_handleCount++;
        if (handle == static_cast<unsigned long>(-1)) {
            handle = m_handleCount++;
        }
        return handle;
    }

    // the names below are not the original's: addRequest queues to m_list, addRequestParallel to m_parallelList
    // (m_subParallelList while m_isSubParallel is set)
    RequestList m_list;
    RequestList m_parallelList;
    RequestList m_subParallelList;
    unsigned long m_handleCount;
    bool m_isSubParallel;
    unsigned char pad_1B071[0x7];
};
}  // namespace gf

#endif

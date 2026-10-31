#ifndef CLASSES_GMK_GMKBDAT_H
#define CLASSES_GMK_GMKBDAT_H

#include "mtl/AllocHandle.h"
#include "mm/mtl/FixStr.h"

namespace fw { class CommonResource; }

namespace gmk {
// table 0x7100B6BEC8
class GmkBdat {
public:
    // what create reads: the memory, the BDAT file's path and an int create copies as is (the names are not the
    // original's)
    struct CreateInfo {
        CreateInfo() : m_param(-1) {}
        mtl::ALLOC_HANDLE m_handle;
        ::mm::mtl::FixStr<256> m_path;
        int m_param;
    };

    // inline: GmkManager's constructor inlines it (no symbol)
    GmkBdat() : m_resource(nullptr), m_assetData(nullptr), m_seq(nullptr) {}
    virtual ~GmkBdat();  // slot 0
    // not virtual: the destructor and its callers call it directly
    void dispose();
    // the step create sets: waits for m_resource, then loads its data into BDAT slot m_createInfo.m_param
    void seqWaitResourceLoaded(float);

    CreateInfo m_createInfo;  // 0x8: create copies it
    // 0x118: the file fw::CommonResource::request returned (create; the name is not the original's)
    fw::CommonResource* m_resource;
    // 0x120: m_resource's asset data, once loaded (seqWaitResourceLoaded; the name is not the original's)
    void* m_assetData;
    // 0x128: the step to run (create sets seqWaitResourceLoaded; the name is not the original's)
    void (GmkBdat::*m_seq)(float);
    // 0x138 bytes: GmkSet holds one at 0x40 and its GmkNpcManager at 0x178 (GmkSet's constructor); the loaded file
    // pointer that followed here is GmkManager's (seqWaitValidateResDefBdatFp stores it at 0x190)
};
}  // namespace gmk

#endif

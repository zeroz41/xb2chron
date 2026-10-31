#ifndef CLASSES_EVENT_STMPACKHEADER_H
#define CLASSES_EVENT_STMPACKHEADER_H

#include "classes/fw/RenderResource.h"
namespace mtl { class ALLOC_HANDLE; }

namespace event {
// table 0x7100B3C400
class StmPackHeader {
public:
    // inline (StmPackMemory::loadStream builds one in each pack)
    StmPackHeader() : m_res(nullptr) {}
    virtual ~StmPackHeader();  // slot 0
    // the handle is unused: the header is requested from MemoryManager's
    void create(mtl::ALLOC_HANDLE handle, const char* name);
    // inline: releases the resource (StmPackMemory::Pack's destructor; the name is not the original's)
    void clear() {
        if (m_res) {
            m_res->release();
            m_res = nullptr;
        }
    }
    // create (0x71000C1790) releases the previous one, then keeps fw::RenderResource::request's (the name is not the
    // original's)
    fw::RenderResource* m_res;  // 0x8
};
}  // namespace event

#endif

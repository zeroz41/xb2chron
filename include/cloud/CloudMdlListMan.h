#ifndef CLOUD_CLOUDMDLLISTMAN_H
#define CLOUD_CLOUDMDLLISTMAN_H

#include "cloud/CloudMdlParts.h"
#include "classes/cloud/CloudMan.h"
#include "mtl/MemManager.h"

namespace cloud {

// the list of a cloud model's parts (0x10: CloudObjMdl holds it at 0x20 before its uniforms at 0x30). The field
// names are not the original's.
class CloudMdlListMan {
public:
    CloudMdlListMan();
    ~CloudMdlListMan();
    void releaseAll();
    void update();
    // one pass that moves each part behind the next one with a smaller sort key
    void calcZSort();

    // inline (CloudMdlDataObj::create, no symbol; the name is not the original's): a new part (kind 10 uniform)
    // at the end of the list. Inline because its allocation handle's stack slot sits above create's own.
    CloudMdlParts* createParts();

    // inline (CloudMdlDataObj::create, no symbol; the name is not the original's)
    void pushBack(CloudMdlParts* parts) {
        if (m_pTail != nullptr) {
            m_pTail->m_pNext = parts;
            parts->m_pPrev = m_pTail;
        } else {
            m_pTop = parts;
        }
        m_pTail = parts;
    }

    CloudMdlParts* m_pTop;   // 0x0
    CloudMdlParts* m_pTail;  // 0x8
};

inline CloudMdlParts* CloudMdlListMan::createParts() {
    CloudMdlParts* parts = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) CloudMdlParts();
    parts->m_uniform.createUniform(CloudUniformType(10), 0);
    pushBack(parts);
    return parts;
}

}  // namespace cloud

#endif

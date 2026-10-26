#include "classes/anm/ResASM.h"

#include "mm/mtl/Vector.h"
#include "string.h"

namespace anm {

ResStateData::ResStateData() : m_pInfo(nullptr) {
    memset(m_attributes, 0, sizeof(m_attributes));
}

void ResStateData::sortAnnotation(unsigned int kind) {
    for (unsigned int i = 0; i < m_clips.size(); i++) {
        if (m_clips[i].m_unsorted) {
            m_clips[i].sortAnnotation(kind);
        }
    }
}

void ResStateData::cleanup() {
    m_pInfo = nullptr;
    for (unsigned int i = 0; i < m_clips.size(); i++) {
        m_clips[i].cleanup();
    }
    for (int kind = 0; kind < 5; kind++) {
        m_enterAnnotations[kind].clear();
        m_leaveAnnotations[kind].clear();
    }
}

}  // namespace anm

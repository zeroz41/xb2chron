#include "classes/RchaNode.h"
#include "ml/EdianUtil.h"

RchaNode::RchaNode() : m_anmCount(0), pad_1994(0), pad_1998(0), m_frameCount(0) {}

void RchaNode::clear() {
    pad_1994 = 0;
    pad_1998 = 0;
    m_frameCount = 0;
    for (int i = 0; i < 48; i++) {
        m_anm[i].clear();
    }
    m_anmCount = 0;
}

bool RchaNode::setup(mtl::ALLOC_HANDLE handle, void const* data) {
    m_allocHandle = handle;
    clear();
    Header* header = const_cast<Header*>(static_cast<const Header*>(data));
    pad_1994 = ml::EdianUtil::read(header->pad_4C);
    pad_1998 = ml::EdianUtil::read(header->pad_4E);
    m_frameCount = ml::EdianUtil::read(header->m_frameCount);
    unsigned int anmCount = ml::EdianUtil::read(static_cast<short>(header->m_anmCount));
    unsigned int* flags = header->m_flags;
    unsigned int* offsets = flags + anmCount;
    unsigned int* ids = offsets + anmCount;
    {
        for (unsigned int i = 0; i < anmCount; i++) {
            unsigned int* value =
                reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(header) + ml::EdianUtil::read(offsets[i]));
            RchaAnm& anm = m_anm[m_anmCount++];
            anm.m_id = ml::EdianUtil::read(ids[i]);
            if (ml::EdianUtil::read(flags[i]) & 1) {
                anm.setValue(ml::EdianUtil::read(*value));
            } else {
                if (header->m_swapped == 0 && !(ml::EdianUtil::read(flags[i]) & 2)) {
                    // the original reads each word through an address computed as an integer: a pointer
                    // index here compiles to one post-incremented pointer instead of the original's two
                    for (int j = 0; j < m_frameCount; j++) {
                        value[j] = ml::EdianUtil::read(
                            *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned long>(value) + j * sizeof(unsigned int)));
                    }
                }
                int count = m_frameCount;
                anm.setTrack(count, value, (ml::EdianUtil::read(flags[i]) & 2) != 0);
            }
        }
    }
    if (header->m_swapped == 0) {
        header->m_swapped = 1;
    }
    return true;
}

unsigned int RchaNode::hashStr(const char* str) const {
    if (str == nullptr) {
        return 0;
    }
    if (str[0] == '\0') {
        return 0;
    }
    unsigned int hash = 0x811C9DC5;
    const char* p = str;
    int count = 0;
    while (*p != '\0' && count < 128) {
        hash = (hash * 0x01000193) ^ static_cast<unsigned char>(*p++);
        count++;
    }
    return hash;
}

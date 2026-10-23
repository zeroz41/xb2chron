#ifndef SKD_DETECTINFO_H
#define SKD_DETECTINFO_H

#include "mm/MMStdBase.h"
#include "mm/Vec3.h"

// skdlib's skd_detect_info.h, as skdlib's own files' include path named it (the only spelling known)
#define SKD_DETECT_INFO_PATH "../../src\\skdlib/multithread/skd_detect_info.h"

namespace skd {
// what a detection job found for one node (0x30 bytes): the node, the push it gets and whether it was hit (the
// names are not the original's: executeDetectSphereJob writes m_push and sets m_hit; DynamicsSolver::solveMT's
// buffer starts with every m_hit clear)
struct DetectInfo {
    DetectInfo() : m_hit(false) {}

    unsigned short m_node;
    unsigned char pad_2[0xE];
    mm::Vec3 m_push;
    bool m_hit;
    unsigned char pad_21[0xF];
};

// the DetectInfos one solve's detection jobs fill (skd_detect_info.h asserts `SIZE > m_size` and `SIZE > index`;
// the names of the members are not the original's)
class DetectInfoBuffer {
public:
    enum { SIZE = 0x800 };

    DetectInfoBuffer() : m_size(0) {}

    // the next unused info
    DetectInfo* alloc() {
#line 61 SKD_DETECT_INFO_PATH
        MM_ASSERT(SIZE > m_size);
        return &m_infos[m_size++];
    }
    DetectInfo& operator[](unsigned long index) {
#line 70 SKD_DETECT_INFO_PATH
        MM_ASSERT(SIZE > index);
        return m_infos[index];
    }
    unsigned int size() const { return m_size; }
    void clear() { m_size = 0; }

    DetectInfo m_infos[SIZE];
    unsigned int m_size;
};
}  // namespace skd

#endif

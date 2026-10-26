#ifndef GRLIB_CGLIBGPUTIMESTAMP_H
#define GRLIB_CGLIBGPUTIMESTAMP_H

#include <string.h>

namespace grlib {
// the GPU's frame time, from command buffer counters (0x68 bytes: the constructor clears them all). The field names
// are not the original's.
class CGLibGpuTimeStamp {
public:
    CGLibGpuTimeStamp();
    ~CGLibGpuTimeStamp();
    void release();
    void reset();
    void begin();
    void end();

    // a timestamp counter report: a slot of the system context's m_occlusion
    struct Report {
        // (inline: no symbol; the name is not the original's)
        void clear() { memset(this, 0, sizeof(*this)); }

        unsigned char* m_pBuff;  // 0x00: the slot (nullptr until first reported)
        unsigned int m_id;  // 0x08: its id
        unsigned int m_offset;  // 0x0C: its offset into the report pool's memory
        bool m_isReported;  // 0x10: end: the report holds a time
    };

    unsigned long m_time;  // 0x00 the measured time (CGLibManager::getGpuTimeStamp returns it)
    Report m_reports[2][2];  // 0x08: [0] begin's, [1] end's, per CGLibManager::s_nDblNowIdx
};
}  // namespace grlib

#endif

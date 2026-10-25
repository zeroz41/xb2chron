#ifndef GRLIB_CGLIBGPUTIMESTAMP_H
#define GRLIB_CGLIBGPUTIMESTAMP_H

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

    unsigned long m_time;  // 0x00 the measured time (CGLibManager::getGpuTimeStamp returns it)
    unsigned char pad_8[0x60];
};
}  // namespace grlib

#endif

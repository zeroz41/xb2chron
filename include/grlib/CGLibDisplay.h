#ifndef GRLIB_CGLIBDISPLAY_H
#define GRLIB_CGLIBDISPLAY_H

#include "nvn/nvn.h"

namespace grlib {
// the display: the window's textures and the sync swapChain waits on (the field names are not the original's;
// the size is not known)
class CGLibDisplay {
public:
    ~CGLibDisplay();
    void setup(NVNdevice* device);
    void resize(unsigned int width, unsigned int height);
    // the next swapChain waits on the sync unless the last frame was signaled
    void updateSignaled();
    void swapChain(NVNqueue* queue);

    unsigned char pad_0[0xFC9];
    bool m_signaled;  // 0xFC9
    unsigned char pad_FCA[0x1];
    bool m_needWait;  // 0xFCB
    unsigned char pad_FCC[0x4];
    NVNsync m_sync;  // 0xFD0
};
}  // namespace grlib

#endif

#ifndef GRLIB_CGLIBDISPLAY_H
#define GRLIB_CGLIBDISPLAY_H

#include "nvn/nvn.h"
#include "grlib/CGLibRenderTarget.h"

namespace grlib {
// the display: the window's textures and the sync swapChain waits on (the field names are not the original's;
// the size is not known). CGLibSystemContext holds it at 0x1110 (CGLibManager::begin calls updateSignaled there).
class CGLibDisplay {
public:
    ~CGLibDisplay();
    void setup(NVNdevice* device);
    void resize(unsigned int width, unsigned int height);
    // the next swapChain waits on the sync unless the last frame was signaled
    void updateSignaled();
    void swapChain(NVNqueue* queue);

    CGLibRenderTarget m_renderTargets[2];  // 0x0: m_index picks the current one
    unsigned char pad_790[0x120];
    CGLibDepthBuffer* m_pDepthBuffer;  // 0x8B0
    unsigned char pad_8B8[0x70C];
    int m_index;  // 0xFC4
    unsigned char pad_FC8[0x1];
    bool m_signaled;  // 0xFC9
    unsigned char pad_FCA[0x1];
    bool m_needWait;  // 0xFCB
    unsigned char pad_FCC[0x4];
    NVNsync m_sync;  // 0xFD0
};
}  // namespace grlib

#endif

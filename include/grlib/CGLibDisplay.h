#ifndef GRLIB_CGLIBDISPLAY_H
#define GRLIB_CGLIBDISPLAY_H

#include "nvn/nvn.h"
#include "nvn/nvn_FuncPtrInline.h"
#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibMemPool.h"

namespace grlib {
// the display: the window's textures and the sync swapChain waits on (the field names are not the original's;
// the size is not known). CGLibSystemContext holds it at 0x1110 (CGLibManager::begin calls updateSignaled there).
class CGLibDisplay {
public:
    // inline: CGLibSystemContext's constructor builds it in place
    CGLibDisplay() {
        m_init = false;
        m_windowInit = false;
        m_textureNum = 0;
        m_storageAlign[1] = 0;
        m_storageAlign[0] = 0;
        m_storageSize[1] = 0;
        m_storageSize[0] = 0;
        m_index = 1;
        m_needWait = true;
        m_signaled = true;
    }
    ~CGLibDisplay();
    // finalizes the syncs, the textures and the window while set up (the destructor and
    // CGLibSystemContext::cleanup inline it; the name is not the original's)
    void release() {
        if (m_init) {
            m_init = false;
            nvnSyncFinalize(&m_sync);
            nvnSyncFinalize(&m_sync2);
            m_renderTargets[0].releaseTexture();
            m_renderTargets[1].releaseTexture();
            nvnWindowFinalize(&m_window);
            m_windowInit = false;
        }
    }
    void setup(NVNdevice* device);
    void resize(unsigned int width, unsigned int height);
    // the next swapChain waits on the sync unless the last frame was signaled
    void updateSignaled();
    void swapChain(NVNqueue* queue);

    CGLibRenderTarget m_renderTargets[2];  // 0x0: m_index picks the current one
    CGLibDepthTarget m_depthTarget;        // 0x790 (its m_pDepthBuffer at 0x8B0)
    CGLibMemPool m_pool;                   // 0xF90
    // 0xFB0: setup's storage sizes and alignments of a 1280x720 window texture, [0] the colour (format 0x25), [1]
    // the depth (format 0x35) one (the names are not the original's)
    unsigned int m_storageSize[2];
    unsigned int m_storageAlign[2];
    unsigned int m_textureNum;  // 0xFC0: cleared as made; what it holds is not known (the name is not the original's)
    int m_index;  // 0xFC4: made 1
    // 0xFC8: the destructor finalizes the syncs, the textures and the window only while it holds, and clears it
    // (the name is not the original's)
    bool m_init;
    bool m_signaled;  // 0xFC9
    bool m_windowInit;  // 0xFCA: the destructor clears it after finalizing the window (the name is not the original's)
    bool m_needWait;  // 0xFCB
    unsigned char pad_FCC[0x4];
    NVNsync m_sync;  // 0xFD0
    NVNsync m_sync2;  // 0x1010: the destructor finalizes it after m_sync (the name is not the original's)
    NVNwindowBuilder m_windowBuilder;  // 0x1050: resize sets the render targets' textures on it (the name is not the original's)
    NVNwindow m_window;  // 0x1090: the destructor finalizes it (0x1210 bytes in all: CGLibUtilObj follows it)
};
}  // namespace grlib

#endif

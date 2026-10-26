#ifndef GRLIB_CGLIBDEVICEOBJ_H
#define GRLIB_CGLIBDEVICEOBJ_H

#include "nvn/nvn.h"
#include "nn/vi.h"

namespace grlib {
// the video interface part of the device (CGLibDeviceObj holds one at 0x5000; its destructor is out of line)
// (the field names are not the original's)
class CGLibDeviceVI {
public:
    ~CGLibDeviceVI();
    // opens the default display, creates a 1280x720 layer on it (preserve-aspect scaling) and gets its native window
    void init();

    nn::vi::NativeWindowHandle m_nativeWindow;  // 0x0
    nn::vi::Display* m_display;                 // 0x8
    nn::vi::Layer* m_layer;                     // 0x10
    int m_width;                                // 0x18
    int m_height;                               // 0x1C
};

// the NVN device and its swap chain (a base of CGLibManager, at 0x8). The field names are not the original's.
class CGLibDeviceObj {
public:
    CGLibDeviceObj();
    bool init();
    void release();
    void swapChain();

    NVNdevice m_device;  // 0x0: CGLibMemPool::setupBuffer builds its pools on it (the name is not the original's)
    NVNqueue m_queue;    // 0x3000: the queue swapChain presents on (the name is not the original's)
    CGLibDeviceVI m_vi;  // 0x5000
};
}  // namespace grlib

#endif

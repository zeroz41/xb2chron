#ifndef GRLIB_CGLIBDEVICEOBJ_H
#define GRLIB_CGLIBDEVICEOBJ_H

#include "nvn/nvn.h"

namespace grlib {
// the video interface part of the device (CGLibDeviceObj holds one at 0x5000; its destructor is out of line)
class CGLibDeviceVI {
public:
    ~CGLibDeviceVI();

    unsigned char pad_0[0x20];
};

// the NVN device and its swap chain (a base of CGLibManager, at 0x8). The field names are not the original's.
class CGLibDeviceObj {
public:
    CGLibDeviceObj();
    bool init();
    void release();
    void swapChain();

    NVNdevice m_device;  // 0x0: CGLibMemPool::setupBuffer builds its pools on it (the name is not the original's)
    unsigned char pad_3000[0x2000];
    CGLibDeviceVI m_vi;  // 0x5000
};
}  // namespace grlib

#endif

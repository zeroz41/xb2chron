#ifndef GRLIB_CGLIBDEVICEOBJ_H
#define GRLIB_CGLIBDEVICEOBJ_H

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

    unsigned char pad_0[0x5000];
    CGLibDeviceVI m_vi;  // 0x5000
};
}  // namespace grlib

#endif

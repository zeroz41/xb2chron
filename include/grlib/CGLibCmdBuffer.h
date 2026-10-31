#ifndef GRLIB_CGLIBCMDBUFFER_H
#define GRLIB_CGLIBCMDBUFFER_H

namespace grlib {
// a command buffer (0xF0 bytes: CGLibSystemContext builds five in a row from 0x88). Its constructor (out of line,
// ScnRenderDrSysParmAcc's unit) clears 0xA8, 0xB0, 0xB8, 0xE0 and 0xE8; what the fields hold is not known.
class CGLibCmdBuffer {
public:
    CGLibCmdBuffer();
    ~CGLibCmdBuffer();

    unsigned char pad_0[0xA8];
    unsigned int pad_A8;
    unsigned char pad_AC[0x4];
    unsigned long pad_B0;
    unsigned long pad_B8;
    unsigned char pad_C0[0x20];
    unsigned long pad_E0;
    unsigned char pad_E8;
    unsigned char pad_E9[0x7];
};
}  // namespace grlib

#endif

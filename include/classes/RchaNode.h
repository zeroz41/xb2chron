#ifndef CLASSES_RCHANODE_H
#define CLASSES_RCHANODE_H

#include "mtl/AllocHandle.h"
#include "rcha/RchaAnm.h"

// table 0x7100B71F80
// The field names are not the original's: setup fills them from the data it is given.
class RchaNode {
public:
    RchaNode();
    // inline: the complete destructor is the copy RchaCam.cpp emitted (0x710063F754), and this file has only
    // the deleting one, with it inlined
    virtual ~RchaNode() {}  // slot 0
    virtual bool setup(mtl::ALLOC_HANDLE handle, void const* data);  // slot 2
    virtual void clear();  // slot 3

    // the head of the data setup reads (the name and field names are not the original's); the three word tables
    // that follow it hold, per anm, its flags (bit 0 a constant, bit 1 compressed), the offset of its value or
    // track from the head, and its id. setup turns the data to this byte order in place, once.
    struct Header {
        unsigned char pad_0[0x48];
        unsigned short m_anmCount;  // 0x48
        short m_frameCount;         // 0x4A
        short pad_4C;               // 0x4C copied to RchaNode::pad_1994; its use is unknown
        short pad_4E;               // 0x4E copied to RchaNode::pad_1998; its use is unknown
        unsigned int m_swapped;     // 0x50 set once the data is in this byte order
        unsigned int m_flags[1];    // 0x54
    };

    // FNV-1 hash of up to 128 characters of `str`, 0 for none or an empty one
    unsigned int hashStr(const char* str) const;

    mtl::ALLOC_HANDLE m_allocHandle;  // 0x8 setup's
    RchaAnm m_anm[48];                // 0x10
    int m_anmCount;                   // 0x1990
    int pad_1994;                     // 0x1994 the data's halfword at 0x4C
    int pad_1998;                     // 0x1998 the data's halfword at 0x4E
    int m_frameCount;                 // 0x199C the data's halfword at 0x4A: every track's frame count
};

#endif

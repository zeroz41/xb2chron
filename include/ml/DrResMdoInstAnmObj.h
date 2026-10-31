#ifndef ML_DRRESMDOINSTANMOBJ_H
#define ML_DRRESMDOINSTANMOBJ_H

namespace ml {
class DrResMdoInstPartsObj;
class DrResMdoPos;
// A model's instanced parts (0x30: release clears six words). Field names are not the original's.
class DrResMdoInstAnmObj {
public:
    struct Header {
        unsigned char pad_0[0x4];
        unsigned int partsMax;  // 0x4 (ScnObjAccSeamPos::getMax)
        // Two runs of m_parts (first index, count) that setupLink links to their positions; the names are not
        // the original's.
        int linkTopB;           // 0x8
        unsigned char pad_C[0xC];
        int linkTopA;           // 0x18
        int linkNumA;           // 0x1C
        unsigned char pad_20[0x8];
        int linkNumB;           // 0x28
        unsigned char pad_2C[0x8];
        int num34;              // 0x34: getWorkSize counts 0x30 bytes per (num34 + linkNumB) (the name is not the original's)
    };
    DrResMdoInstAnmObj();
    void release();
    void setupLink(DrResMdoPos* pos) const;
    // the work bytes the header's objects take, rounded up to 0x10 (getWorkSize multiplies linkTopB by 0x78 and
    // linkTopA by 0x28 + 0x160, so those two are counts too)
    static unsigned int getWorkSize(const unsigned char* data);

    const Header* m_header;           // 0x0
    DrResMdoInstPartsObj** m_parts;   // 0x8: partsMax objects
    unsigned char pad_10[0x20];
};
}  // namespace ml

#endif

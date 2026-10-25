#ifndef ML_DRRESMDOINSTANMOBJ_H
#define ML_DRRESMDOINSTANMOBJ_H

namespace ml {
class DrResMdoInstPartsObj;
// a model's instanced parts (0x30: release clears six words). Field names are not the original's.
class DrResMdoInstAnmObj {
public:
    struct Header {
        unsigned char pad_0[0x4];
        unsigned int partsMax;  // 0x4 (ScnObjAccSeamPos::getMax)
    };
    DrResMdoInstAnmObj();
    void release();

    const Header* m_header;           // 0x0
    DrResMdoInstPartsObj** m_parts;   // 0x8: partsMax objects
    unsigned char pad_10[0x20];
};
}  // namespace ml

#endif

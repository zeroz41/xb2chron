#ifndef ML_DRRESMDOLODOBJ_H
#define ML_DRRESMDOLODOBJ_H

namespace ml {
// Only release is declared so far.
class DrResMdoLodObj {
public:
    // builds the object at work (its data follows it); returns setup's result
    // the model data's header: the LOD resource sits m_lodOfs bytes from it when FLAG_LOD is set in m_flags
    // (struct, field and flag names are not the original's)
    struct MdoHeader {
        unsigned char pad_0[0x2];
        unsigned char m_flags;  // 0x2
        unsigned char pad_3[0x89];
        unsigned int m_lodOfs;  // 0x8C
        enum { FLAG_LOD = 1 << 1 };
    };
    struct MdoLod {
        unsigned char pad_0[0x8];
        unsigned int m_grpNum;  // 0x8: one 0x20-byte group work each, plus one
        unsigned char pad_C[0x4];
        unsigned int m_partsNum;  // 0x10: one 0x20-byte parts work each, plus one
    };
    // the object, (m_grpNum + 1) group works and (m_partsNum + 1) parts works
    static unsigned int calcWorkSize(const unsigned char* data);
    static unsigned int create(unsigned char* work, const unsigned char* data);
    unsigned int setup(const unsigned char* data, unsigned char* work);
    static void release(DrResMdoLodObj*& obj);
    unsigned char pad_0[0x1C];  // create places the object's data 0x30 bytes after it
    // 0x1C: DrMdoCtlNom's alpha passes pass it to DrMdoCtl::createWeightVtx, which tests bit i per part (the name is
    // not the original's)
    unsigned int m_dispBits;
    unsigned char pad_20[0x10];
};
}  // namespace ml

#endif

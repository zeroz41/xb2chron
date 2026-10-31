#ifndef ML_DRRESMDOALPTBL_H
#define ML_DRRESMDOALPTBL_H

#include "grlib/CGLibVtxInstans.h"

namespace ml {
class DrResMdoLodObj;
class DrResMdoMeshObj;

// A model's per-part alpha table (0x50 bytes, then the work create lays out after it: m_num floats rounded up to
// 4, then one bit per part). Field and struct names are not the original's.
class DrResMdoAlpTbl {
public:
    struct MdoHeader {
        unsigned char pad_0[0x2];
        unsigned char m_flags;  // 0x2
        unsigned char pad_3[0x8D];
        unsigned int m_alpOfs;  // 0x90
        enum { FLAG_ALPTBL = 1 << 2 };
    };
    struct AlpHeader {
        unsigned int m_dataOfs;  // 0x0, from this header
        int m_num;               // 0x4
    };

    static unsigned int calcWorkSize(const unsigned char* data);
    static unsigned int create(unsigned char* work, const unsigned char* data);
    static void release(DrResMdoAlpTbl*& obj);
    void update(float rate, const DrResMdoLodObj* lod, const DrResMdoMeshObj* mesh);

    grlib::CGLibVtxInstans m_inst;  // 0x0
    float* m_alpha;                 // 0x30: in the work right after the object
    unsigned int* m_bits;           // 0x38: after m_alpha
    const unsigned char* m_data;    // 0x40
    unsigned int m_num;             // 0x48
};
}  // namespace ml

#endif

#ifndef ML_DRIBLOBJ_H
#define ML_DRIBLOBJ_H

#include "grlib/CGLibTextureBuffer.h"

namespace ml {
class DrIBLColiAcc;
class DrMan;

// One IBL resource ('GIBL', version 10000): two texture arrays of m_texNum textures built from it and the
// collision accessor. Only what the destructor uses is declared; the field names are not the original's.
class DrIBLObj {
public:
    ~DrIBLObj();
    void initialize(DrMan* drMan);

    const void* m_data;  // 0x0, the resource
    unsigned char pad_8[0x38];
    unsigned int m_texNum;  // 0x40, from the resource's header (+0x8)
    grlib::CGLibTextureBuffer* m_texA;  // 0x48, new[] m_texNum
    grlib::CGLibTextureBuffer* m_texB;  // 0x50, new[] m_texNum
    unsigned int m_flags;  // 0x58, initialize sets bit 0
    DrIBLColiAcc* m_coliAcc;  // 0x60
};
}  // namespace ml

#endif

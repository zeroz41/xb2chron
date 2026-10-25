#ifndef ML_DRRESSHDMPF_H
#define ML_DRRESSHDMPF_H

#include "ml/DrShdDataObj.h"

namespace ml {

namespace _drrsm {
// The declaration names DrResShdMpf looks up ("MODE_UMATE_ON", "DECL_DIT...").
extern const char* c_DeclOfsNames[2];
}  // namespace _drrsm

// A multi-pass-fur shader's settings: select values and the current shader's uniform block offsets in
// m_shaderSel, and the offsets of the two declarations setupShader sets from its index bits.
class DrResShdMpf {
public:
    DrResShdMpf(DrShdDataObj* data, int type);
    void setupShader(unsigned int idx);

    // Field names are not the original's.
    DrShdDataObj* m_data;          // 0x0
    int m_shaderSel[8];            // 0x8
    unsigned short m_flags;        // 0x28: bit 0 while the constructor sets up
    unsigned short m_type;         // 0x2A
    int m_declOfs[2];              // 0x2C: offsets of _drrsm::c_DeclOfsNames
};
}  // namespace ml

#endif

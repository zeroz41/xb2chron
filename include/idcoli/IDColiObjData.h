#ifndef IDCOLI_IDCOLIOBJDATA_H
#define IDCOLI_IDCOLIOBJDATA_H

#include "classes/idcoli/IDColiObjBase.h"

namespace mm { class Mat44; }

namespace idcoli {
// a collision object built from collision data (1.0.0's table _ZTVN6idcoli13IDColiObjDataE derives it from
// IDColiObjBase); IDColiParmsCharacter and IDColiParmsBone reach a character's through it. Only the members their
// code uses are declared; the field names are not the original's.
class IDColiObjData : public IDColiObjBase {
public:
    void createBinary(const void* data);
    const char* getBoneName(int index) const;
    void setBoneMatrix(int index, const mm::Mat44& matrix);

    unsigned char pad_1d0[0x28];
    int m_boneNum;  // 0x1F8, IDColiParmsBone::getBoneMax
    unsigned char pad_1fc[0x24];
    float m_adsorption;  // 0x220, IDColiParmsCharacter::setAdsorption
};
}  // namespace idcoli

#endif

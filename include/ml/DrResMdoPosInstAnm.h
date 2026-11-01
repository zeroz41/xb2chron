#ifndef ML_DRRESMDOPOSINSTANM_H
#define ML_DRRESMDOPOSINSTANM_H

#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ml {
// Only the instance position animation callbacks, their table and the fields DrResMdoInstPartsAnm uses are declared
// so far.
// pos points at translation, rotation, scale (three mm::Vec3).
class DrResMdoPosInstAnm {
public:
    typedef void (*AnmInsPosFunc)(mm::Vec3* pos, float value);
    static void anmInsPosParm_TranX(mm::Vec3* pos, float value);
    static void anmInsPosParm_TranY(mm::Vec3* pos, float value);
    static void anmInsPosParm_TranZ(mm::Vec3* pos, float value);
    static void anmInsPosParm_RotX(mm::Vec3* pos, float value);
    static void anmInsPosParm_RotY(mm::Vec3* pos, float value);
    static void anmInsPosParm_RotZ(mm::Vec3* pos, float value);
    static void anmInsPosParm_SclX(mm::Vec3* pos, float value);
    static void anmInsPosParm_SclY(mm::Vec3* pos, float value);
    static void anmInsPosParm_SclZ(mm::Vec3* pos, float value);

    static AnmInsPosFunc s_pCallAnmInsPos[9];

    void update();
    void getAnmMatrix(mm::Mat44* mtx, float frame) const;

    // Field names are not the original's (DrResMdoInstPartsAnm reads and writes them).
    unsigned char pad_0[0x20];
    mm::Mat44 m_matrix;             // 0x20: DrResMdoInstPartsAnm::getMatrix copies it when no matrix was set
    unsigned char pad_60[0x30];
    mm::Mat44 m_setMatrix[2];       // 0x90: per DrMan double-buffer stock index (DrResMdoInstPartsAnm::setMatrix)
    unsigned char pad_110[0x40];
    unsigned short m_setMatrixFlags;  // 0x150: bit n = m_setMatrix[n] set (DrResMdoInstPartsAnm::setMatrix)
    unsigned short m_frameMax;      // 0x152: DrResMdoInstPartsAnm::get*PosMaxFrame scales it
};
}  // namespace ml

#endif

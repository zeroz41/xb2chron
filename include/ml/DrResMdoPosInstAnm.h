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

    void setup(float frame);
    void update();
    void getAnmMatrix(mm::Mat44* mtx, float frame) const;

    // The 0x70-byte block setup copies from m_res whole (one memcpy); the names are not the original's.
    struct Data {
        mm::Mat44 matrix;               // 0x0
        unsigned char pad_40[0xC];
        float radius;                   // 0x4C: times the matrix's z-axis length gives m_data.radius
        mm::Vec3 center;                // 0x50: setup/update transform m_res->center by the matrix into m_data.center
        unsigned char pad_60[0x10];
    };

    // Field names are not the original's (DrResMdoInstPartsAnm reads and writes them).
    unsigned char pad_0[0x10];
    const Data* m_res;              // 0x10: setup copies it to m_data
    unsigned char pad_18[0x8];
    Data m_data;                    // 0x20: the current matrix and bounding sphere
    mm::Mat44 m_setMatrix[2];       // 0x90: per DrMan double-buffer stock index (DrResMdoInstPartsAnm::setMatrix)
    mm::Mat44 m_anmMatrix;          // 0x110: setup's getAnmMatrix result; update saves the previous m_data.matrix here
    // 0x150: bit n = m_setMatrix[n] set (DrResMdoInstPartsAnm::setMatrix); 0x80 = m_anmMatrix holds the previous
    // matrix; update sets 0x4 when the bounding sphere is clipped, 0x8/0x10/0x20 from clipDirShadowChk's 0x3800 bits
    unsigned short m_setMatrixFlags;
    unsigned short m_frameMax;      // 0x152: DrResMdoInstPartsAnm::get*PosMaxFrame scales it; updateSwitch sets it
    unsigned short m_frameStart;    // 0x154: DrResMdoInstPartsAnm::updateSwitch sets it
};
}  // namespace ml

#endif

#ifndef ML_DRRESMDOPOSINSTANM_H
#define ML_DRRESMDOPOSINSTANM_H

#include "mm/Vec3.h"

namespace ml {
// Only the instance position animation callbacks and their table are declared so far.
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
};
}  // namespace ml

#endif

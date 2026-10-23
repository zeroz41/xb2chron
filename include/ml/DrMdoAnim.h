#ifndef ML_DRMDOANIM_H
#define ML_DRMDOANIM_H

#include "mm/Vec3.h"
namespace ml { class DrResMdoMat; }

namespace ml {
// Only the static animation callbacks and their tables are declared so far.
class DrMdoAnim {
public:
    static void animcall_UV_Scr_U(DrResMdoMat*, float*, float);
    static void animcall_UV_Scr_V(DrResMdoMat*, float*, float);
    static void animcall_UV_Trans_U(DrResMdoMat*, float*, float);
    static void animcall_UV_Trans_V(DrResMdoMat*, float*, float);
    static void animcall_UV_Rot(DrResMdoMat*, float*, float);
    static void animcall_WorkFloat1(DrResMdoMat*, float*, float);
    static void animcall_MatAlpha(DrResMdoMat*, float*, float);
    static void animcall_MatColorR(DrResMdoMat*, float*, float);
    static void animcall_MatColorG(DrResMdoMat*, float*, float);
    static void animcall_MatColorB(DrResMdoMat*, float*, float);

    static void anmNodeParm_TranX(mm::Vec3*, float);
    static void anmNodeParm_TranY(mm::Vec3*, float);
    static void anmNodeParm_TranZ(mm::Vec3*, float);
    static void anmNodeParm_RotX(mm::Vec3*, float);
    static void anmNodeParm_RotY(mm::Vec3*, float);
    static void anmNodeParm_RotZ(mm::Vec3*, float);
    static void anmNodeParm_SclX(mm::Vec3*, float);
    static void anmNodeParm_SclY(mm::Vec3*, float);
    static void anmNodeParm_SclZ(mm::Vec3*, float);

    static void (*s_pCallAnim[10])(DrResMdoMat*, float*, float);
    static void (*s_pCallAnmNode[9])(mm::Vec3*, float);
};
}  // namespace ml

#endif

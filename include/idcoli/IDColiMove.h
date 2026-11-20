#ifndef IDCOLI_IDCOLIMOVE_H
#define IDCOLI_IDCOLIMOVE_H

#include "idcoli/IDColiResult.h"
#include "mm/Vec3.h"

namespace idcoli { class IDColiObj; }

namespace idcoli {
// one collision-checked move of an object, built on the stack (0x200 bytes)
class IDColiMove {
public:
    // calcWallHitChkVec's scratch (calcColiStateParams keeps one on the stack: 0x100 bytes)
    struct wrlResTempVec {
        // the horizontal directions (x, z; length 1) to the wall hits calcWallHitChkVec has kept, m_wallCount of
        // them (names inferred)
        struct Dir {
            float x;
            float z;
        };
        Dir m_dir[32];
    };

    IDColiMove();
    void setShapeParms(float parm0, float parm1);
    void setFloor(float floor);
    void setAccuracy(bool accuracy);
    // moves `obj` by `move` as far as the collision allows; m_result holds how far it went
    bool moveColi(IDColiObj* obj, mm::Vec3 const& move);
    // moves a body standing at `pos` by `move` against the grand objects; true when it ended on the ground
    bool moveColi(mm::Vec3 const& pos, mm::Vec3 const& move);
    // m_move = move, the per-move flags cleared, m_slopeCos and the horizontal back direction m_backDir
    void setupParms(mm::Vec3 const& move);
    // splits `move` into m_stepCount steps of m_step (one per m_shapeParms[0] of its length, times 2/3/5/8)
    void calcCheckParams(mm::Vec3 const& move);
    // m_result = m_pos at the height the vertical hits allow: the highest upward-facing hit within two radii above
    // m_pos.y, else the highest one below the lowest downward-facing hit under `top`
    void calcColiYVecParms(float top);
    bool testWallCheck();
    void calcColiBaseParms(wrlResTempVec* temp);
    bool testVecYCheck(mm::Vec3 const& top);
    bool moveDataColi();
    bool moveDefColi();
    // pushes m_pos out of each hit by m_shapeParms[0] (along the base segment when m_baseFlag); m_hit = whether a
    // hit facing up is a wall (calcWallHitChkVec)
    void calcColiShapeParms();
    // pad_1f4 |= whether a hit (m_coliResult.pad_d8/m_slopeCos choose which) is a wall for calcWallHitChkVec, on a move down
    bool calcColiStateParams();
    bool calcWallHitChkVec(mm::Vec3 const& normal, mm::Vec3 const& pos, wrlResTempVec* temp);

    // GfComBehaviorPc::detectHead sets these three and m_coliResult.m_ignoreMaterial (0x1000D) before its moveColi (meaning not known)
    bool pad_0;
    bool pad_1;
    bool pad_2;
    unsigned char pad_3;
    float pad_4;  // testWallCheck's input.m_instSizeMin (where IDColiDef keeps its m_radiusSq)
    void* pad_8;
    // 0x10, the hits of a move: moveColi points m_tblPos/m_tblNormal at two 32-entry stack arrays and pad_d8 at a
    // bit per hit, m_type 2 (a table); m_skipObj is the object moved (null for a move without one). The test*
    // functions hand it to the grand, character and grdChar tests. The name is inferred.
    IDColiResult m_coliResult;
    int m_wallCount;  // 0x120, the entries of the caller's wrlResTempVec (calcColiShapeParms clears it; name inferred)
    unsigned int pad_124;
    unsigned char pad_128[8];
    mm::Vec3 m_result;  // moveColi's: the move it allowed (the whole move for an object it skips)
    mm::Vec3 m_move;  // 0x140, setupParms
    mm::Vec3 m_pos;  // 0x150, the position being checked (moved by m_step per step)
    mm::Vec3 m_startPos;  // 0x160
    mm::Vec3 m_basePos;  // 0x170, IDColiPrimitive::s_CallBasePos's position
    mm::Vec3 m_baseOffset;  // 0x180, IDColiPrimitive::s_CallBasePos's offset
    mm::Vec3 m_step;  // 0x190, calcCheckParams
    mm::Vec3 m_backDir;  // 0x1A0, -m_move flattened to y 0 and normalized (setupParms; valid when m_hasBackDir)
    float m_halfLength;  // 0x1B0, half of m_move's length
    float m_stepLength;  // 0x1B4, m_step's length
    float m_shapeParms[2];  // 0x1B8, setShapeParms (the constructor's 1 and 2); s_CallBasePos's radius and height
    float m_slopeAngle;  // 0x1C0, degrees (the constructor's 45); setupParms keeps its cosine in m_slopeCos
    float m_floor;  // 0x1C4, setFloor
    float m_adsorption;  // 0x1C8, the object's IDColiObjData::m_adsorption (the constructor's 0.05)
    float m_radiusSq;  // 0x1CC, m_shapeParms[0] squared
    float m_slopeCos;  // 0x1D0
    float pad_1d4;
    float pad_1d8;
    int m_stepCount;  // 0x1DC, calcCheckParams
    IDColiObj* m_baseObj;  // 0x1E0, the object moved (null for a move without one)
    bool pad_1e8;
    bool pad_1e9;
    bool m_baseFlag;  // 0x1EA, IDColiPrimitive::s_CallBasePos's flag
    bool m_hit;  // 0x1EB, moveColi(pos, move)'s result
    bool pad_1ec;
    bool m_accuracy;  // 0x1ED, setAccuracy
    bool pad_1ee;
    bool pad_1ef;  // calcCheckParams multiplies the step count further when set, and clears it
    bool pad_1f0;
    bool pad_1f1;
    bool pad_1f2;
    bool m_hasBackDir;  // 0x1F3, setupParms: m_backDir is valid (an accurate move with a horizontal part)
    bool pad_1f4;
    bool pad_1f5;
    unsigned char pad_1f6[0xA];
};
}  // namespace idcoli

#endif

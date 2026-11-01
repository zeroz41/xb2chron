#ifndef GF_GFFIELDLOOKIK_H
#define GF_GFFIELDLOOKIK_H

#include "mm/Vec3.h"

class CBdatWrapper;
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// no table: an object's look-at ik (gf_game_stuck_meter's unit); GfComBehaviorMob keeps one at 0x210, its
// TFieldExecCmdTurn next at 0x250 (0x40 bytes). Field names are the constructor's and dispose's uses
class GfFieldLookIk {
public:
    explicit GfFieldLookIk(GF_OBJ_HANDLE* handle);
    ~GfFieldLookIk() { dispose(); }
    void dispose();
    // the object's settings from its row of a table with LookAt (0: none, 1..2: the solver) and LookAtRange columns
    void create(GF_OBJ_HANDLE* handle, const CBdatWrapper& bdat, int id);
    void update(float deltaTime);  // 0x71002D2964
    // the point to look at on the object: its answer to MsgPcGetLookPoint, else its world position; false when it
    // has neither
    bool findPos(mm::Vec3& pos) const;
    // the point the object looks at: the gimmicks' interest position in mode 1, else the party leader's answer to
    // MsgPcGetLookPoint; false when there is none
    bool findTargetPos(mm::Vec3& pos) const;
    bool isCondMatched(const mm::Vec3& pos) const;
    // fades the solver in or out by isCondMatched and eases pad_20 towards the target position
    template <typename T>
    void updateIkSolver(T& solver);

    GF_OBJ_HANDLE* m_handle;  // -1 without one
    // which of the object's GfComIK solvers dispose fades out (3 at first; the name is not the original's)
    unsigned int m_solverIndex;
    float pad_c;  // 5 at first
    float pad_10;  // 3 pi / 4 at first
    float pad_14;  // pi / 3 at first
    float m_fadeTime;  // 0.7 at first: dispose's LookIkSolver::fadeOut time (the name is not the original's)
    bool pad_1c;  // true at first
    unsigned char pad_1d[0x3];
    mm::Vec3 pad_20;  // zero at first
    bool pad_30;  // false at first; dispose clears it
    unsigned char pad_31[0xF];
};
}  // namespace gf

#endif

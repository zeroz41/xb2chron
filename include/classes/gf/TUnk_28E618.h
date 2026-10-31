#ifndef CLASSES_GF_TUNK_28E618_H
#define CLASSES_GF_TUNK_28E618_H

#include "classes/fw/Camera.h"
#include "classes/gf/TUnk_B52C38.h"
#include "mm/Vec3.h"
#include "mm/Mat44.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class TUnk_B535D0; }
namespace gmk { class AGmkBase; }

namespace gf {
// a class with no table (named after its constructor 0x710028E618): the 0x58-byte object TUnk_B535D0's setup
// fn_7100291100 makes (gf_game_arena.cpp line 111) and keeps at +0xC8. Its constructor keeps the arena at +0 and
// zeroes +8 and +0x50; layout not recovered.
class TUnk_28E618 {
public:
    // Placeholder name (constructor): new in 3.0.1, nothing in 1.0.0's place names it; its code (fn_710028E618) is in
    // unit_710028E5BC's range.
    explicit TUnk_28E618(TUnk_B535D0* owner);
    // fn_710028E624 (placeholder code address; TUnk_B535D0::fn_7100291B64 runs it before freeing the object)
    ~TUnk_28E618();

    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: TUnk_B537B0's steps call them
    // on the arena's +0xC8 object (this one); their code is in unit_710028E5BC / unit_710028EBB0 next to this
    // class's constructor. What they do (they repeat GfGameSalvage's camera-cut and treasure-box code):
    // fn_710028EB74: when m_gmks holds one, its first gimmick's matrix (gmk::AGmkBase::getMatrix) into mtx; answers
    // whether it did (GfGameSalvage::getEventTbox's shape).
    bool fn_710028EB74(mm::Mat44& mtx) const;
    // fn_710028EBB0: GimmickCamera::create("salvage_cut01", pos, rotY) into m_camera, setAuto(false)
    // (GfGameSalvage::createCameraCut01's code).
    void fn_710028EBB0(const mm::Vec3& pos, float rotY);
    // fn_710028ECA0: pops m_camera from CameraManager's layer 0 (1.0f) while pushed, then drops it
    // (GfGameSalvage::destroyCameraCut01's code).
    void fn_710028ECA0();
    // fn_710028ED50: pushes m_camera on layer 0 (0.0f) unless pushed, then GimmickCamera::play
    // (GfGameSalvage::playCameraCut01's code).
    void fn_710028ED50();
    // fn_710028EDAC: refills m_gmks with up to 8 gimmicks of type 0x3C from every GmkManager set.
    void fn_710028EDAC();
    // fn_710028E7DC: how many of the score's row TresureNeed1..3 values (GfBdatBtl fn_71001EA2E8 slots 0-2) the
    // score's m_value reaches (0..3).
    int fn_710028E7DC(const TUnk_B52C38::Score& score);
    // fn_710028E69C / fn_710028E878: the result step's two branches (fn_710028E7DC's answer nonzero / zero); not
    // recovered.
    void fn_710028E69C(const TUnk_B52C38::Score& score);
    void fn_710028E878(const TUnk_B52C38::Score& score);
    // fn_710028EF70: plays one of four voices (ml::mtRand(4)) from the table at 0x7100B6AD58, row = fn_710028E7DC's count.
    void fn_710028EF70(const TUnk_B52C38::Score& score);
    // fn_710028F00C: counts the drivers GfGameParty::getHandleDriver(0..2, 0) gives and passes them, (count != 0)
    // and flag to fn_710056B9CC.
    void fn_710028F00C(bool flag);
    // fn_710028F0A4: when the score's row has a ClearReward (GfBdatBtl fn_71001EA1C4), GfFobjDropitem::emitDropitems
    // with that item.
    void fn_710028F0A4(const TUnk_B52C38::Score& score);

    TUnk_B535D0* m_owner;  // (the name is not the original's)
    // GimmickCamera::create's camera cut (the name is not the original's)
    mm::mtl::IntrusivePtr<fw::Camera> m_camera;
    // the type-0x3C gimmicks fn_710028EDAC collects: the constructor zeroes only the size at +0x50, the destructor
    // empties it before releasing m_camera, fn_710028EB74 reads its first (the name is not the original's)
    mm::mtl::FixedVector<gmk::AGmkBase*, 8> m_gmks;
};
}  // namespace gf

#endif

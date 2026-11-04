#ifndef CLASSES_GF_TUNK_28E618_H
#define CLASSES_GF_TUNK_28E618_H

#include "classes/fw/Camera.h"
#include "classes/gf/GfArenaBattle.h"
#include "mm/Vec3.h"
#include "mm/Mat44.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfGameArena; }
namespace gmk { class AGmkBase; }

namespace gf {
// a class with no table (named after its constructor 0x710028E618): the 0x58-byte object GfGameArena's setup
// initialize makes (gf_game_arena.cpp line 111) and keeps at +0xC8. Its constructor keeps the arena at +0 and
// zeroes +8 and +0x50; layout not recovered.
class GfArenaReward {
public:
    // 2.0.0's symbols name it.
    explicit GfArenaReward(GfGameArena* owner);
    // fn_710028E624 (placeholder code address; GfGameArena::finalize runs it before freeing the object)
    ~GfArenaReward();

    // 2.0.0's symbols name them. StateArenaResultBattle's steps call them on the arena's +0xC8 object (this one); their
    // code is in unit_710028E5BC / unit_710028EBB0 next to this class's constructor. What they do (they repeat
    // GfGameSalvage's camera-cut and treasure-box code): getActionOrigin: when m_gmks holds one, its first gimmick's
    // matrix (gmk::AGmkBase::getMatrix) into mtx; answers whether it did (GfGameSalvage::getEventTbox's shape).
    bool getActionOrigin(mm::Mat44& mtx) const;
    // createCameraCut01: GimmickCamera::create("salvage_cut01", pos, rotY) into m_camera, setAuto(false)
    // (GfGameSalvage::createCameraCut01's code).
    void createCameraCut01(const mm::Vec3& pos, float rotY);
    // destroyCameraCut01: pops m_camera from CameraManager's layer 0 (1.0f) while pushed, then drops it
    // (GfGameSalvage::destroyCameraCut01's code).
    void destroyCameraCut01();
    // playCameraCut01: pushes m_camera on layer 0 (0.0f) unless pushed, then GimmickCamera::play
    // (GfGameSalvage::playCameraCut01's code).
    void playCameraCut01();
    // listUpTBox: refills m_gmks with up to 8 gimmicks of type 0x3C from every GmkManager set.
    void listUpTBox();
    // fn_710028E7DC: how many of the score's row TresureNeed1..3 values (GfBdatBtl getBTL_ChBtlTresureNeed slots 0-2) the
    // score's m_value reaches (0..3).
    int fn_710028E7DC(const GfArenaBattle::Score& score);
    // fn_710028E69C / fn_710028E878: the result step's two branches (fn_710028E7DC's answer nonzero / zero); not
    // recovered.
    void fn_710028E69C(const GfArenaBattle::Score& score);
    void fn_710028E878(const GfArenaBattle::Score& score);
    // fn_710028EF70: plays one of four voices (ml::mtRand(4)) from the table at 0x7100B6AD58, row = fn_710028E7DC's count.
    void fn_710028EF70(const GfArenaBattle::Score& score);
    // playReturnVoice: counts the drivers GfGameParty::getHandleDriver(0..2, 0) gives and passes them, (count != 0)
    // and flag to createReturnVoice.
    void playReturnVoice(bool flag);
    // fn_710028F0A4: when the score's row has a ClearReward (GfBdatBtl getBTL_ChBtlClearReward), GfFobjDropitem::emitDropitems
    // with that item.
    void fn_710028F0A4(const GfArenaBattle::Score& score);

    GfGameArena* m_owner;  // (the name is not the original's)
    // GimmickCamera::create's camera cut (the name is not the original's)
    mm::mtl::IntrusivePtr<fw::Camera> m_camera;
    // the type-0x3C gimmicks listUpTBox collects: the constructor zeroes only the size at +0x50, the destructor
    // empties it before releasing m_camera, getActionOrigin reads its first (the name is not the original's)
    mm::mtl::FixedVector<gmk::AGmkBase*, 8> m_gmks;
};
}  // namespace gf

#endif

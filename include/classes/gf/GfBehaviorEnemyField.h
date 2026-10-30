#ifndef CLASSES_GF_GFBEHAVIORENEMYFIELD_H
#define CLASSES_GF_GFBEHAVIORENEMYFIELD_H

namespace gf { class GfComBehaviorEnemy; }
namespace gmk { class GmkRouteNavi; }
namespace navi { class NvmshAcObj; }
namespace gf { namespace enemy { enum STATE_ID : int; } }

namespace gf {
// table 0x7100B65E10; GfComBehaviorEnemy's field movement, embedded in it at 0x140 (its constructor stores this
// table at 0x140; the field states pass owner+0x140 to these functions)
class GfBehaviorEnemyField {
public:
    // a field move speed (StateFieldBlade::enter passes 0, StateFieldHome::seqWaitTurnEnd and
    // StateFieldAreaWalk::seqMoveToGoal 1; the values' names are not known)
    enum MoveSpeed : int {};
    virtual ~GfBehaviorEnemyField();  // slot 0
    // whether the enemy reached its goal (pad_c0) within pad_18, or its local steer timed out colliding
    bool isArrivedToGoal() const;
    // the route navigation of its gimmick, none without one
    gmk::GmkRouteNavi* getGmkRouteNavi() const;
    void moveToGoal(float dt);
    void applyFieldMoveSpeed(enemy::STATE_ID state, GfComBehaviorEnemy& owner);
    void applyFieldMoveSpeed(MoveSpeed speed, GfComBehaviorEnemy& owner);
    void applyFieldMoveSpeed(MoveSpeed speed, MoveSpeed speed2, GfComBehaviorEnemy& owner);
    unsigned char pad_8[0x10];
    // how near the goal counts as arrived (isArrivedToGoal compares the squared distance with its square;
    // StateFieldAreaWalk::isCondMatch with a type 0 gimmick's first float)
    float pad_18;
    unsigned char pad_1c[0x24];
    // its navigation mesh object (StateFieldAreaWalk::seqMoveToGoal asks canGetMoveVec of it)
    navi::NvmshAcObj* pad_40;
    unsigned char pad_48[0x78];
    // the goal position (isArrivedToGoal; the field states set it before turning or moving to it). Three floats:
    // an mm::Vec3 would make the class 16-aligned
    float pad_c0;
    float pad_c4;
    float pad_c8;
    // the class's end is not known: it reaches at least 0x5270 (the destructor disposes a member at 0x5268); it is
    // taken to end where GfComBehaviorEnemy's pad_545c (owner+0x545c) begins
    unsigned char pad_cc[0x524C];
};
}  // namespace gf

#endif

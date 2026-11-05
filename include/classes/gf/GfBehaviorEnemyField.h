#ifndef CLASSES_GF_GFBEHAVIORENEMYFIELD_H
#define CLASSES_GF_GFBEHAVIORENEMYFIELD_H

#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfFieldEnemySensor.h"
#include "gf/SDataEnemy.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "classes/gmk/GmkSquadNavi.h"
#include "gf/GfFieldMoveSpeed.h"
#include "gf/GfFieldPitchRollController.h"

namespace fw { class ColiMoveObject; }
namespace gf { class GfComBehaviorEnemy; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class IGfBehFieldOwner; }
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
    // the first block of the ninth param list (fw::ParamManager::m_paramLists[8]): applyLinearVelocityAndRotY
    // limits a frame's fall to pad_4 - 0.1 (the struct's name is not the original's)
    struct FallParam {
        float pad_0;
        float pad_4;
    };
    // its table's key function: disposes, then its members go (the D2 copy follows TFieldExecCmdTurn's)
    virtual ~GfBehaviorEnemyField();  // slot 0
    void dispose();
    void applyLinearVelocityAndRotY(float dt);
    // disposes its squad place, then joins the squad of its object's enemy gimmick (type 0 or 1) when it has one
    void createSquadNavi();
    // disposes its sensor, then creates it at the owner's transform with its object's rows and battle lock info
    void createSensor();
    // advances the field movement by dt (GfComBehaviorEnemy::updateField calls it each frame)
    void update(float dt);
    // whether the enemy reached its goal (pad_c0) within pad_18, or its local steer timed out colliding
    bool isArrivedToGoal() const;
    // the route navigation of its gimmick, none without one
    gmk::GmkRouteNavi* getGmkRouteNavi() const;
    // its object's first collision object when that is a move object (GfComBehaviorNpc::getColiObject's shape)
    fw::ColiMoveObject* getColiObject() const;
    void moveToGoal(float dt);
    // moves its navigation mesh object on toward the goal unless it arrived (isArrivedToGoal)
    void updateNaviMeshObj(float dt);
    // the direction to move in: its navigation mesh object's move vector, else toward the goal (level unless it
    // flies), normalized
    void getMoveDir(mm::Vec3& dir) const;
    void applyFieldMoveSpeed(enemy::STATE_ID state, GfComBehaviorEnemy& owner);
    // the move speed a state runs at (1.0.0's name; inline in this build): 0 for states 1..7, 1 for 8, 9 and
    // 13..15, 2 for 10 and 11, else 0
    MoveSpeed getFieldMoveSpeedType(enemy::STATE_ID state) const {
        if (state >= 1 && state <= 7) {
            return MoveSpeed(0);
        }
        if (state >= 8 && state <= 9) {
            return MoveSpeed(1);
        }
        if (state >= 10 && state <= 11) {
            return MoveSpeed(2);
        }
        if (state >= 13 && state <= 15) {
            return MoveSpeed(1);
        }
        return MoveSpeed(0);
    }
    // its object's walk and run speeds (SDataEnemy's; 1.0.0's names, inline in this build)
    float getWalkSpeed() const {
        DataParamAcc acc(m_handle);
        return acc.getSDataEnemy()->m_walkSpeed;
    }
    float getRunSpeed() const {
        DataParamAcc acc(m_handle);
        return acc.getSDataEnemy()->m_runSpeed;
    }
    void applyFieldMoveSpeed(MoveSpeed speed, GfComBehaviorEnemy& owner);
    void applyFieldMoveSpeed(MoveSpeed speed, MoveSpeed speed2, GfComBehaviorEnemy& owner);
    // its owner and the owner's object (the names are not the original's)
    IGfBehFieldOwner* m_owner;
    GF_OBJ_HANDLE* m_handle;
    // how near the goal counts as arrived (isArrivedToGoal compares the squared distance with its square;
    // StateFieldAreaWalk::isCondMatch with a type 0 gimmick's first float)
    float pad_18;
    // how far above the goal still counts (isArrivedToGoal)
    float pad_1c;
    // 3 (flying, SDataEnemy::m_actType's value) counts the height in isArrivedToGoal's distance
    unsigned char pad_20;
    unsigned char pad_21[0xb];
    // moveToGoal turns its velocity toward the facing only while the angle between them is above this (and at
    // most pad_30)
    float pad_2c;
    // the turn threshold GfComBehaviorEnemy::execTurnCmd(float) passes to its turn command (CreateInfo::pad_c)
    float pad_30;
    unsigned char pad_34[0x2];
    // its getEnemeyMoveParam index (applyFieldMoveSpeed)
    unsigned char pad_36;
    // set while the enemy belongs to a squad gimmick's members (GfComBehaviorEnemy::isOtherMemberHome)
    bool pad_37;
    unsigned char pad_38[0x8];
    // its navigation mesh object (StateFieldAreaWalk::seqMoveToGoal asks canGetMoveVec of it)
    navi::NvmshAcObj* pad_40;
    unsigned char pad_48[0x8];
    // its place in its squad (the name is not the original's)
    gmk::GmkSquadNavi m_squadNavi;
    // cleared while the enemy floats at the water surface (update with SDataEnemy::m_actType 1); gravity pulls
    // only while set
    bool pad_90;
    unsigned char pad_91[0xf];
    // the velocity applyLinearVelocityAndRotY moves its collision object by (update clears x and z each frame and
    // lets gravity act on y; the name is not the original's)
    mm::Vec3 m_velocity;
    // the turn speed applyLinearVelocityAndRotY turns the object by (update clears it)
    float pad_b0;
    unsigned char pad_b4[0xc];
    // the goal position (isArrivedToGoal; updateNaviMeshObj hands it to its navigation mesh object as the end
    // position, so it is a Vec3; the name is not the original's)
    mm::Vec3 m_goalPos;
    // the names of these four are not the original's
    GfFieldEnemySensor m_sensor;
    GfEnemyFieldMoveSpeed m_moveSpeed;
    GfFieldLocalSteer m_localSteer;
    // the local steer's TIsTargetNotSameSquad<GfComBehaviorEnemy> (the constructor stores its table here)
    unsigned char pad_5260[0x8];
    GfFieldPitchRollController m_pitchRoll;
    // update counts pad_52a4 up by dt while it is below pad_52a0
    float pad_52a0;
    float pad_52a4;
    unsigned char pad_52a8;
    // set when the enemy is where its act type cannot stay (out of water for 1, in it for 0, under it for 2;
    // update), GfComBehaviorEnemy::updateField's state 13 condition
    bool pad_52a9;
    unsigned char pad_52aa[0x6];
};
}  // namespace gf

#endif

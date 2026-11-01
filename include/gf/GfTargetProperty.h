#ifndef GF_GFTARGETPROPERTY_H
#define GF_GFTARGETPROPERTY_H

#include "mm/Plane.h"
#include "classes/gf/GfObjProperty.h"

namespace gf {

// no table: what an object's property tells those who target or follow it (a GfObjProperty points at one, a driver's
// at its own +0xC0, which GfComPropertyPc's procMsgObjectFlushProperty fills and the PC AI reads). Not 1.0.0's
// GfTargetProperty (GfComProperty's, below, holds a handle where this holds its state). The class and field names
// are not the original's.
class GfObjProperty::TargetInfo {
public:
    // GfObjPropertyDriver's and GfObjPropertyBlade's constructors build their own (inline: its cost is 265, so the
    // poses go in the body and m_position copies pad_10). The wall plane starts facing x (its sqrtf of 1 stays).
    TargetInfo()
        : m_state(0), pad_50(mm::Vec3::unitY, 0.0f), pad_70(0), pad_78(0), pad_79(0), pad_7A(0), pad_7B(0),
          pad_7C(0), m_gmkTutorialOK(false), m_onWall(false), m_isMoving(false), m_blocksFollowWarp(false),
          m_wallPlane(mm::Vec3(1.0f, 0.0f, 0.0f), 0.0f), pad_B0(0), pad_B4(1), pad_B8(0), pad_C0(-1), pad_C8(0) {
        pad_10 = mm::Vec3::zero;
        pad_20 = mm::Quat::identity;
        m_position[0] = pad_10.x;
        m_position[1] = pad_10.y;
        m_position[2] = pad_10.z;
        pad_40 = mm::Quat::identity;
    }
    // what the object is doing, by the PC's flush: 0 none of the below, 1, 2, 3 while its field status has bit 4
    // (isFollowBuddyPc does not follow a PC in state 3), 4, 5, 6
    int m_state;
    unsigned char pad_4[0xC];
    mm::Vec3 pad_10;  // zero from the constructor
    mm::Quat pad_20;  // the identity from the constructor
    // the object's position: the PC's flush copies its transform's world position (GfEffectGround compares the
    // water's height with its y)
    float m_position[3];
    unsigned char pad_3c[0x4];
    mm::Quat pad_40;   // the identity from the constructor
    mm::Plane pad_50;  // facing up through the origin from the constructor
    long pad_70;
    unsigned char pad_78;
    unsigned char pad_79;
    unsigned char pad_7A;
    unsigned char pad_7B;
    unsigned char pad_7C;
    // GfGameManager::isGmkTutorialOK answers it for a leader in state 1 (the name is not the original's)
    bool m_gmkTutorialOK;
    // the PC's GfPropertyField::flashWallInfo: whether it is on a wall (the name is not the original's)
    bool m_onWall;
    // the PC's flush: any of its motion is not zero (velocity, m_moveVec2, locomotion, m_moveSpeed)
    bool m_isMoving;
    // the PC's flush: set while the PC's word at 0x120 is 1; TaskFieldCheckWarp::update warps no PC that follows a
    // player with it (nor one in state 1 or 5)
    bool m_blocksFollowWarp;
    unsigned char pad_81[0xF];
    // the PC's GfPropertyField::flashWallInfo: the plane of the wall it is on, else facing up through the origin
    // (the name is not the original's)
    mm::Plane m_wallPlane;
    int pad_B0;
    int pad_B4;  // 1 from the constructor
    int pad_B8;
    long pad_C0;  // -1 from the constructor
    int pad_C8;
};

// no table: the object's target, as GfComProperty keeps it (1.0.0's UniquePtr<gf::GfTargetProperty> names the type;
// GfComProperty::recieveMessage stores MsgGameChangeTarget's handle in it, flush copies it to the character
// property, GfObjAcc reads it)
class GfTargetProperty {
public:
    gf::GF_OBJ_HANDLE* m_target;  // the target, -1 for none (the name is not the original's)
};
}  // namespace gf

#endif

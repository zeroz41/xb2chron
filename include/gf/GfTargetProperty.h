#ifndef GF_GFTARGETPROPERTY_H
#define GF_GFTARGETPROPERTY_H

namespace gf {

// no table: what an object's property tells those who target or follow it (GfComProperty holds one through a
// UniquePtr, 1.0.0's UniquePtr<gf::GfTargetProperty> names the type; a GfObjProperty points at one, a driver's at
// its own +0xC0, which GfComPropertyPc's procMsgObjectFlushProperty fills and the PC AI reads). The field names are
// not the original's.
class GfTargetProperty {
public:
    // what the object is doing, by the PC's flush: 0 none of the below, 1, 2, 3 while its field status has bit 4
    // (isFollowBuddyPc does not follow a PC in state 3), 4, 5, 6
    int m_state;
    unsigned char pad_4[0x2C];
    // the object's position: the PC's flush copies its transform's world position (GfEffectGround compares the
    // water's height with its y)
    float m_position[3];
    unsigned char pad_3c[0x41];
    // GfGameManager::isGmkTutorialOK answers it for a leader in state 1 (the name is not the original's)
    bool m_gmkTutorialOK;
    unsigned char pad_7e[0x1];
    // the PC's flush: any of its motion is not zero (velocity, m_moveVec2, locomotion, m_moveSpeed)
    bool m_isMoving;
    // the PC's flush: set while the PC's word at 0x120 is 1; TaskFieldCheckWarp::update warps no PC that follows a
    // player with it (nor one in state 1 or 5)
    bool m_blocksFollowWarp;
};

}  // namespace gf

#endif

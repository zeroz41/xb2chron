#ifndef GF_GFTARGETPROPERTY_H
#define GF_GFTARGETPROPERTY_H

namespace gf {

// no table: what an object's property tells those who target or follow it (GfComProperty holds one through a
// UniquePtr, 1.0.0's UniquePtr<gf::GfTargetProperty> names the type; GfComPropertyPc's procMsgObjectFlushProperty
// fills a PC's). The field names are not the original's.
class GfTargetProperty {
public:
    // what the object is doing, by the PC's flush: 0 none of the below, 1, 2, 3 while its field status has bit 4
    // (isFollowBuddyPc does not follow a PC in state 3), 4, 5, 6
    int m_state;
    unsigned char pad_4[0x7B];
    // the PC's flush: any of its motion is not zero (velocity, m_moveVec2, locomotion, m_moveSpeed)
    bool m_isMoving;
};

}  // namespace gf

#endif

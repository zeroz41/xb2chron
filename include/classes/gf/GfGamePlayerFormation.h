#ifndef CLASSES_GF_GFGAMEPLAYERFORMATION_H
#define CLASSES_GF_GFGAMEPLAYERFORMATION_H

#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/Transform.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGamePlayerFormation; }

namespace gf {
// table 0x7100B558C0
class GfGamePlayerFormation : public ::mm::mtl::PtrSingleton< ::gf::GfGamePlayerFormation>, public ::fw::MessageObject {
public:
    // one per player index (GfComPropertyPc::m_setupKind); 1.0.0's findPlayer searches six of them by handle.
    // The names are not the original's.
    struct Player {
        // the index of the player it follows, -1 for none (getFollowTransform then takes its own)
        unsigned int m_followIndex;
        GF_OBJ_HANDLE* m_handle;  // the player's object
        // set: the field AI's follow tests look at the player's own motion, not at the one it follows
        bool m_standalone;
    };

    virtual ~GfGamePlayerFormation();  // slot 0
    // the transform the player at index follows: the one of the player it follows, its own without one
    const fw::Transform& getFollowTransform(unsigned int index) const;

    // where the player at each index is to go (the field AI's sensor copies it into its blackboard; the name is
    // not the original's)
    mm::Vec3 m_targetPos[6];
    unsigned char pad_80[0xC0];
    fw::Transform m_followTransforms[6];  // getFollowTransform's (the name is not the original's)
    unsigned char pad_200[0x60];
    Player m_players[6];  // (the name is not the original's)
};
}  // namespace gf

#endif

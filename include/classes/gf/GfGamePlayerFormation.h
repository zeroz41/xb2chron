#ifndef CLASSES_GF_GFGAMEPLAYERFORMATION_H
#define CLASSES_GF_GFGAMEPLAYERFORMATION_H

#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/Transform.h"
#include "mm/Vec3.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGamePlayerFormation; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B558C0
class GfGamePlayerFormation : public ::mm::mtl::PtrSingleton< ::gf::GfGamePlayerFormation>, public ::fw::MessageObject {
public:
    // one per player index (GfComPropertyPc::m_setupKind); findPlayer searches them by handle (1.0.0 had six, 3.0.1
    // nine). The names are not the original's.
    struct Player {
        Player() : m_followIndex(-1), m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_standalone(true) {}

        // the index of the player it follows, -1 for none (getFollowTransform then takes its own)
        unsigned int m_followIndex;
        GF_OBJ_HANDLE* m_handle;  // the player's object
        // set: the field AI's follow tests look at the player's own motion, not at the one it follows
        bool m_standalone;
    };

    // build inlines it (1.0.0 has a copy; 3.0.1 none)
    GfGamePlayerFormation() : m_formation(0), m_flip(false) {}
    virtual ~GfGamePlayerFormation();  // slot 0

    static void build(const GfSetupParam& param);
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    // 1.0.0's: every position zero, every rotation none (build inlines it; 3.0.1 has no copy)
    void setup(const GfSetupParam& param) {
        for (int i = 0; i < 9; i++) {
            m_targetPos[i] = mm::Vec3::zero;
            m_formationPos[i] = mm::Vec3::zero;
            m_followTransforms[i].position = mm::Vec3::zero;
            m_followTransforms[i].rotation = mm::Quat::identity;
        }
    }
    void updateImpl(const fw::UpdateInfo& info);
    // where the player at index stands in the formation around transform
    void calcTargetTransform(const fw::Transform& transform, unsigned int index, mm::Vec3* pOut) const;
    // whether another player near the player at index stands in its way to target (1.0.0's; 3.0.1 inlines it)
    bool stopPlayer(unsigned int index, const mm::Vec3& target, float radius) {
        float radiusSq = radius * radius;
        const mm::Vec3& pos = m_followTransforms[index].position;
        for (unsigned int i = 0; i < 9; i++) {
            if (i == index) {
                continue;
            }
            if (m_players[i].m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                continue;
            }
            if (!m_players[i].m_standalone && m_players[i].m_followIndex == index) {
                continue;
            }
            const mm::Vec3& other = m_followTransforms[i].position;
            mm::Vec3 toOther(other.x - pos.x, 0.0f, other.z - pos.z);
            if (toOther.dot(toOther) <= radiusSq) {
                mm::Vec3 toTarget(target.x - pos.x, 0.0f, target.z - pos.z);
                mm::Vec3 fromTarget(other.x - target.x, 0.0f, other.z - target.z);
                float ahead = toOther.dot(toTarget);
                float behind = fromTarget.dot(toTarget * -1.0f);
                float lenSq = fromTarget.dot(fromTarget);
                if ((ahead >= 0.0f && behind >= 0.0f) || lenSq <= radiusSq) {
                    return true;
                }
            }
        }
        return false;
    }
    // the transform the player at index follows: the one of the player it follows, its own without one
    const fw::Transform& getFollowTransform(unsigned int index) const;
    void swapFormation(GF_OBJ_HANDLE* handle0, GF_OBJ_HANDLE* handle1);
    // the index of the player with handle, -1 for none
    unsigned int findPlayer(GF_OBJ_HANDLE* handle);
    void swapFormation(unsigned int index0, unsigned int index1);
    // whether the player with handle is too far from the leader for a random talk
    bool isFarRandomTalk(GF_OBJ_HANDLE* handle);

    // where the player at each index is to go (the field AI's sensor copies it into its blackboard; the name is
    // not the original's)
    mm::Vec3 m_targetPos[9];
    // its place in the formation, before the navigation test (the name is not the original's)
    mm::Vec3 m_formationPos[9];
    fw::Transform m_followTransforms[9];  // each player's world transform (the name is not the original's)
    Player m_players[9];  // (the name is not the original's)
    // which FormationParam: 1 while the battle leader is a driver (1.0.0's changeFormation sets it, 0-3)
    unsigned int m_formation;
    bool m_flip;  // set: the formation's sideways offsets are mirrored (the name is not the original's)
};
}  // namespace gf

#endif

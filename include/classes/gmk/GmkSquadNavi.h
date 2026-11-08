#ifndef CLASSES_GMK_GMKSQUADNAVI_H
#define CLASSES_GMK_GMKSQUADNAVI_H

#include "classes/gmk/GmkSquad.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusiveList.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gmk {
// no table: one object's place in a squad (GmkSquad::addGmkSquadNavi/removeGmkSquadNavi take it). 0x40 bytes
// (GfComBehaviorMob keeps one at 0xC0; getPosRotY reads the Vec3 at 0x30). The member functions are 1.0.0's; the
// field names are not the original's
class GmkSquadNavi : public ::mm::mtl::IntrusiveListNodeBase {
public:
    // what create copies into the navi whole (one struct copy: its words are stored last to first) and what
    // dispose resets it to: the squad, the object and two values update compares against (GfComBehaviorMob::
    // createSquadNavi starts from these defaults). The field names are not the original's
    struct CreateInfo {
        CreateInfo() : m_squad(nullptr), m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), pad_10(0.1f), pad_14(1.0f) {}
        GmkSquad* m_squad;
        gf::GF_OBJ_HANDLE* m_handle;  // -1 without one
        float pad_10;
        float pad_14;
    };
    // what update takes: the member's position, zero by default (StateFieldSquadMember::update fills it from its
    // transform; the field's name is not the original's)
    struct UpdateInfo {
        UpdateInfo() : m_pos(::mm::Vec3::zero) {}
        ::mm::Vec3 m_pos;
    };
    // dispose's defaults (GfComBehaviorMob's constructor stores the same values)
    GmkSquadNavi() : m_index(-1), pad_30(::mm::Vec3::zero) {}
    ~GmkSquadNavi() { dispose(); }
    void create(const CreateInfo& info);
    // leaves its squad (when it has one and an object) and resets m_info
    void dispose();
    // while it is in a squad (isInSquad) whose leader is bound (GmkSquad::getBindedGmkSquadLeader): its member's
    // position and y rotation (GmkSquad::getPosRotY) with pad_30 added to the position; false otherwise
    bool getPosRotY(::mm::Vec3& pos, float& rotY) const;
    // its symbol names it: follows the squad leader with the member's position (GmkElevator's unit)
    void update(const UpdateInfo& info);
    // it has a squad and an object, and its index is one of the squad's members (GfComBehaviorMob::isSquadMember
    // tests the same); the name is not the original's
    bool isInSquad() const;

    CreateInfo m_info;  // 0x10 (the name is not the original's)
    int m_index;  // its place among the squad's members; 0 is the leader's (GfComBehaviorMob::isSquadMember)
    unsigned char pad_2c[0x4];
    // 0x30: getPosRotY adds it to the member position (GfComBehaviorMob's constructor zeroes it)
    ::mm::Vec3 pad_30;
};
inline bool GmkSquadNavi::isInSquad() const {
    return m_info.m_squad != nullptr && m_info.m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && m_index >= 0 &&
           static_cast<unsigned int>(m_index) < m_info.m_squad->pad_70;
}
}  // namespace gmk

#endif

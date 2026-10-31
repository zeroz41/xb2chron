#ifndef CLASSES_GMK_GMKSQUADNAVI_H
#define CLASSES_GMK_GMKSQUADNAVI_H

#include "mm/mtl/IntrusiveList.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gmk { class GmkSquad; }

namespace gmk {
// no table: one object's place in a squad (GmkSquad::addGmkSquadNavi/removeGmkSquadNavi take it). 0x30 bytes
// (GfComBehaviorMob keeps one at 0xC0, its Vec3 next at 0xF0). The member functions are 1.0.0's; the field names
// are not the original's
class GmkSquadNavi : public ::mm::mtl::IntrusiveListNodeBase {
public:
    struct CreateInfo;
    struct UpdateInfo;
    // dispose's defaults (GfComBehaviorMob's constructor stores the same values)
    GmkSquadNavi() : m_squad(nullptr), m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), pad_20(0.1f), pad_24(1.0f), m_index(-1) {}
    ~GmkSquadNavi() { dispose(); }
    void create(const CreateInfo& info);
    // leaves its squad (when it has one and an object) and resets the squad, handle and pad_20/pad_24
    void dispose();

    GmkSquad* m_squad;
    gf::GF_OBJ_HANDLE* m_handle;  // -1 without one
    float pad_20;
    float pad_24;
    int m_index;  // its place among the squad's members; 0 is the leader's (GfComBehaviorMob::isSquadMember)
    unsigned char pad_2c[0x4];
};
}  // namespace gmk

#endif

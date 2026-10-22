#ifndef CLASSES_GF_GFGAMEINSIDEBATTLELOCK_H
#define CLASSES_GF_GFGAMEINSIDEBATTLELOCK_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Map.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameInsideBattleLock; }
namespace gf { class GfSetupParam; }
namespace mm { class Vec3; }

namespace gf {
// table 0x7100B548F8: whether the field's enemies stand inside a battle-lock gimmick's shape, kept per enemy
class GfGameInsideBattleLock : public ::mm::mtl::PtrSingleton< ::gf::GfGameInsideBattleLock> {
public:
    GfGameInsideBattleLock() : m_hasLock(false) {}
    virtual ~GfGameInsideBattleLock();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    void updateInfos();
    static void updateInfo(GF_OBJ_HANDLE* handle);
    bool isInsideBattleLock(GF_OBJ_HANDLE* handle) const;
    static bool isInside(GF_OBJ_HANDLE* handle);
    static bool isInside(const mm::Vec3& pos);
    template <typename T>
    void updateInfoByGmk();

    // whether each enemy stands inside a battle lock (updateInfos's; the name is not the original's)
    mm::mtl::Map<GF_OBJ_HANDLE*, bool> m_infos;
    bool m_hasLock;  // update sets it while any of the gimmick sets' battle-lock gimmicks holds something
};
}  // namespace gf

#endif

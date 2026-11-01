#ifndef CLASSES_GF_GFGAMEOBJENEMY_H
#define CLASSES_GF_GFGAMEOBJENEMY_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedQueue.h"

namespace gf { class GfGameObjEnemy; }
namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B550F8
// (0x8AC0 bytes: GfGameObj::initialize news it)
class GfGameObjEnemy : public ::mm::mtl::PtrSingleton< ::gf::GfGameObjEnemy> {
public:
    // 16 bytes, 8-aligned (FixedList<GINFO, 64>::erase is this unit's: its nodes are 24 bytes)
    struct GINFO {
        unsigned long pad_0;
        unsigned long pad_8;
    };
    // two enemies whose genus link calcGenusLink works out (24 bytes; update queues them)
    struct Pair {
        Pair() = default;
        // enterEnemyObj queues a pair so (no link yet, no bones)
        Pair(GF_OBJ_HANDLE* first, GF_OBJ_HANDLE* second)
            : pad_0(first), pad_8(second), pad_10(false), pad_12(-1), pad_14(-1) {}

        GF_OBJ_HANDLE* pad_0;  // none: -1
        GF_OBJ_HANDLE* pad_8;  // none: -1
        bool pad_10;  // calcGenusLink clears and sets it
        short pad_12;
        short pad_14;  // a bone index, -1 for none (calcGenusLink's getBoneTransform)
    };

    GfGameObjEnemy() {}  // inline: GfGameObj::initialize builds it in place
    virtual ~GfGameObjEnemy();  // slot 0
    // works out up to 8 queued pairs' genus links, each queued again, until the first one comes round again
    void update(const fw::UpdateInfo& info);
    void calcGenusLink(Pair& pair);

    mm::mtl::FixedList<GINFO, 64> pad_8;
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 256> pad_670;
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 256> pad_1890;
    mm::mtl::FixedQueue<Pair, 1024> pad_2ab0;  // update's pairs
    void enterEnemyObj(GF_OBJ_HANDLE* handle);  // GfGameObj::flushEvent: an object entered the game
    void leaveEnemyObj(GF_OBJ_HANDLE* handle);  // GfGameObj::flushEvent: an object left the game
};
}  // namespace gf

#endif

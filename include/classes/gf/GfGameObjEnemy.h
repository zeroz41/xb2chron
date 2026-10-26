#ifndef CLASSES_GF_GFGAMEOBJENEMY_H
#define CLASSES_GF_GFGAMEOBJENEMY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameObjEnemy; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B550F8
class GfGameObjEnemy : public ::mm::mtl::PtrSingleton< ::gf::GfGameObjEnemy> {
public:
    virtual ~GfGameObjEnemy();  // slot 0
    void enterEnemyObj(GF_OBJ_HANDLE* handle);  // GfGameObj::flushEvent: an object entered the game
    void leaveEnemyObj(GF_OBJ_HANDLE* handle);  // GfGameObj::flushEvent: an object left the game
};
}  // namespace gf

#endif

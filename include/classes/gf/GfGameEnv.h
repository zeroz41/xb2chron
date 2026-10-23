#ifndef CLASSES_GF_GFGAMEENV_H
#define CLASSES_GF_GFGAMEENV_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace mm { class Vec3; }

namespace gf { class GfGameEnv; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// table 0x7100B54838
class GfGameEnv : public ::mm::mtl::PtrSingleton< ::gf::GfGameEnv> {
public:
    virtual ~GfGameEnv();  // slot 0
    static bool isRoom();
    static unsigned int getMapJumpID();
    static int getMapID();
    static void setMapID(unsigned int, unsigned int);
    static bool isMapjump();
    static bool isMapjumpWithSaveData();
    static void gevGameState(GF_STATE, GF_STATE);
    static void sendPlayerPositionToRender(const mm::Vec3& pos);
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFGAMEENV_H
#define CLASSES_GF_GFGAMEENV_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace mm { class Vec3; }

namespace gf { class GfGameEnv; }
namespace gf {
// the handles GfGameEnv's create functions return (GfGameEvent keeps them, 0 for none)
enum CFILTER_HANDLE : int;
enum CLOUD_SEA_HANDLE : int;
enum CLOUD_SEA : int;
enum CLOUD_SEA_PRIO : int;
}
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// table 0x7100B54838
class GfGameEnv : public ::mm::mtl::PtrSingleton< ::gf::GfGameEnv> {
public:
    virtual ~GfGameEnv();  // slot 0
    static bool isRoom();
    static unsigned int getMapJumpID();
    static int getMapID();
    static void destroyColorFilter(CFILTER_HANDLE handle);  // GfGameEvent::finalize's
    static CLOUD_SEA_HANDLE createCloudSea(CLOUD_SEA type, CLOUD_SEA_PRIO prio);
    static void destroyCloudSea(CLOUD_SEA_HANDLE handle);
    static void setMapID(unsigned int, unsigned int);
    static bool isMapjump();
    static bool isMapjumpWithSaveData();
    static void gevGameState(GF_STATE, GF_STATE);
    static void sendPlayerPositionToRender(const mm::Vec3& pos);
    static void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);
    static void clear();
};
}  // namespace gf

#endif

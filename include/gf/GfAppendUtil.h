#ifndef GF_GFAPPENDUTIL_H
#define GF_GFAPPENDUTIL_H
#include "gf/GFATTACH.h"

namespace gf { class GF_OBJ_HANDLE; class GfAppendInfo; class GfInitParamDriver; }

namespace gf {
// sets up what objects append to others (functions, by its symbols)
class GfAppendUtil {
public:
    static void setupWeapon(GFATTACH attach, GfAppendInfo& info, unsigned int weaponId, unsigned int driverId,
                            unsigned int bladeId, bool flag);
    static void setupPartyBlade(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int weaponId, unsigned int driverId,
                                unsigned int bladeId);
    static void setupEnemyBlade(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int id, GF_OBJ_HANDLE* owner,
                                GF_OBJ_HANDLE* blade);
    static void setupEnemyBladeWithNoDriver(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int id,
                                            GF_OBJ_HANDLE* blade);
    static void setupActViewer(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int weaponId, unsigned int driverId,
                               unsigned int bladeId);
    static void setupExtraModel(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* owner);
    static void setupBelonging(GF_OBJ_HANDLE* handle, unsigned int a, unsigned int b, unsigned int c, unsigned int d);
    static void setupEnemy(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int enArrangeId, GF_OBJ_HANDLE* owner);
    static void setupEventActEnemy(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int enArrangeId);
    static void setupBelongingForDriver(GF_OBJ_HANDLE* handle, const GfInitParamDriver& param);
};
}  // namespace gf

#endif

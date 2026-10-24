#ifndef CLASSES_GF_GFFIELDGIMMICK_H
#define CLASSES_GF_GFFIELDGIMMICK_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; class MapjumpCallbackInfo; class GF_OBJ_HANDLE; enum GEV : int; enum RELOAD_BDAT : int; }
namespace fw { class UpdateInfo; }

namespace gf {
// static helpers of gf_field_gimmick.cpp (only the ones gf_field_locator calls are declared)
// a PtrSingleton: GfPlayComEventFade reaches it through PtrSingleton<GfFieldGimmick>::sys()
class GfFieldGimmick : public ::mm::mtl::PtrSingleton< ::gf::GfFieldGimmick> {
public:
    // the FLD_maplist id of the map an RSC_GmkSetList row belongs to
    static int getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(int gmkSetId);
    // whether the map's gimmick sets are ready (GfAutoTalkManager::seqInit waits for it)
    static bool isGmkSetReady();
    // GfFieldManager's forwards (its initialize, finalize and update call them)
    static void build(const GfSetupParam& param);
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has GmkCtrlVolSeManager::update(float)
    // directly followed by GfFieldGimmick::createGmkSet). A member because its unit's functions are GfFieldGimmick's
    // (it sits before createGmkSet). What it does: nothing (a bare return); GfFieldManager::postUpdate calls it last,
    // passing its fw::UpdateInfo.
    static void fn_710026B74C(const fw::UpdateInfo& info);
    unsigned char pad_8[0xF4A4];
    // an event fade is running: GfPlayComEventFade's update sets it as it starts the fade, its end() clears it
    // (the name is not the original's)
    bool m_eventFade;
};
}  // namespace gf

#endif

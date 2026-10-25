#ifndef CLASSES_GF_GFFIELDLOD_H
#define CLASSES_GF_GFFIELDLOD_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldLod; }
namespace gf { class GfSetupParam; class MapjumpCallbackInfo; class GF_OBJ_HANDLE; enum GEV : int; enum RELOAD_BDAT : int; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B51EB0
class GfFieldLod : public ::mm::mtl::PtrSingleton< ::gf::GfFieldLod> {
public:
    virtual ~GfFieldLod();  // slot 0
    bool isPlayAnimEnd(int anim) const;
    // GfFieldManager's forwards (its initialize, finalize, clear, update and gev* functions call them)
    static void build(const GfSetupParam& param);
    static void destroy();
    static void validateByInitData();
    static void update(const fw::UpdateInfo& info);
    void gevMapjump(GEV gev, const MapjumpCallbackInfo& info);
    void gevPlayEvent(GEV gev, unsigned int eventId);
    int findBdatIdByLodId(unsigned short lodId) const;
    // true when a part of the LOD model animates (GfFieldMapGimmick::seqLod_init then waits for the animation's end)
    bool setAnimReverse(int bdatId, bool flag0, bool flag1);
    void setFade(int bdatId, bool flag0, bool flag1);
    void setLodSwitchId(int bdatId, unsigned int switchId);
    bool isFadeOut(int bdatId) const;  // GfGameEvent::isMapLodDisp's: not shown
    bool isAnimReverse(int bdatId) const;  // GfGameEvent::isMapLodAnimReverse's
};
}  // namespace gf

#endif

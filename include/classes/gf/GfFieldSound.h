#ifndef CLASSES_GF_GFFIELDSOUND_H
#define CLASSES_GF_GFFIELDSOUND_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldSound; }
namespace gf { class GfSetupParam; class MapjumpCallbackInfo; class GF_OBJ_HANDLE; enum GEV : int; enum RELOAD_BDAT : int; }
namespace fw { class UpdateInfo; class SoundPack; }

namespace gf {
// table 0x7100B525B8
class GfFieldSound : public ::mm::mtl::PtrSingleton< ::gf::GfFieldSound> {
public:
    virtual ~GfFieldSound();  // slot 0
    // GfFieldManager's forwards (its initialize, finalize, clear, update, postUpdate and gev* functions call them)
    static void build(const GfSetupParam& param);
    static void destroy();
    void clear();
    void update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    void gevPlayEvent(GEV gev, unsigned int eventId);
    void gevBattleEnd();
    void gevGameMapModel(GF_OBJ_HANDLE* handle, bool flag);
    void gevMapjump(GEV gev, const MapjumpCallbackInfo& info);
    void gevPause(unsigned int flags0, unsigned int flags1);
    // the sound packs its +0x28 and +0x38 hold (GfFieldMapGimmick picks one by a row's "flag" bit)
    fw::SoundPack* getCommonPack();
    fw::SoundPack* getMapPack();
};
}  // namespace gf

#endif

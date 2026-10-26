#ifndef CLASSES_GF_GFGAMEVOICE_H
#define CLASSES_GF_GFGAMEVOICE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameVoice; class GAME_VOICE_HANDLE; class GF_OBJ_HANDLE; enum CV_RESULT : int; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }

namespace gf {
// table 0x7100B56B40
class GfGameVoice : public ::mm::mtl::PtrSingleton< ::gf::GfGameVoice> {
public:
    virtual ~GfGameVoice();  // slot 0
    static void gevLayerPause(unsigned int, bool);
    // SCOM_FIELD_VOICE::exec stops a voice it cuts short, then asks how it ended
    static void playStop(GAME_VOICE_HANDLE* voice);
    // plays the named voice ("702870101"), handing back its handle for getResult
    static GAME_VOICE_HANDLE* playVoice(const char* name);
    static CV_RESULT getResult(GAME_VOICE_HANDLE* voice);
    static CV_RESULT getResult(GF_OBJ_HANDLE* handle);  // the voice of an object (GfGameUtil::isPlayVoice: 2 playing)
    bool isPlayEnemyVoice() const;
    static void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);
    bool isPlayVoice(gf::GF_OBJ_HANDLE* handle) const;
};
}  // namespace gf

#endif

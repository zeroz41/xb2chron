#ifndef CLASSES_GF_SCOM_SALVAGE_VOICE_H
#define CLASSES_GF_SCOM_SALVAGE_VOICE_H

namespace gf { class GF_OBJ_HANDLE; class GAME_VOICE_HANDLE; enum CV_SALVAGE : int; enum CV_SALVAGE_RESULT : int; }

namespace gf {
// no table in 3.0.1: GfGameSalvage plays its voices through these statics (GfSalvageVoice's forwards)
class SCOM_SALVAGE_VOICE {
public:
    static GAME_VOICE_HANDLE* create(GF_OBJ_HANDLE* handle, CV_SALVAGE voice);
    static GAME_VOICE_HANDLE* createResult(GF_OBJ_HANDLE* handle, CV_SALVAGE_RESULT voice);
    static bool isPlayEnd(GAME_VOICE_HANDLE* voice);  // GfGameVoice::getResult is no longer 2 (playing)
};
}  // namespace gf

#endif

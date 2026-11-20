#ifndef GF_GFSALVAGEVOICE_H
#define GF_GFSALVAGEVOICE_H

namespace gf { class GF_OBJ_HANDLE; class GAME_VOICE_HANDLE; }
// CV_SALVAGE is unsigned: GfSalvageVoice::playVoice zero-extends it to index its tables (an enum with no negative
// value and no fixed type has unsigned int underneath)
namespace gf { enum CV_SALVAGE : unsigned int; enum CV_SALVAGE_RESULT : int; }  // the salvage voice's kind and result kind

namespace gf {
// the salvage voices (gf_game_voice.cpp): SCOM_SALVAGE_VOICE's create functions forward here
class GfSalvageVoice {
public:
    static GAME_VOICE_HANDLE* playVoice(GF_OBJ_HANDLE* handle, CV_SALVAGE voice);
    static GAME_VOICE_HANDLE* playResultVoice(GF_OBJ_HANDLE* handle, CV_SALVAGE_RESULT voice);
};
}  // namespace gf

#endif

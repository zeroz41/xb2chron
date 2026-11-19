#ifndef GF_GFFIELDVOICE_H
#define GF_GFFIELDVOICE_H

namespace gf { struct ParamObj; class GAME_VOICE_HANDLE; }
// CV_FIELD is unsigned: GfFieldVoice::playVoice zero-extends it to index its tables (an enum with no negative
// value and no fixed type has unsigned int underneath)
namespace gf { enum CV_FIELD : unsigned int; enum CV_PRIO : int; }  // the field voice's kind and priority

namespace gf {
// the field voices (gf_game_voice.cpp): SCOM_FIELD_VOICE's create functions and exec call these with a ParamObj
// built on their stack
class GfFieldVoice {
public:
    static GAME_VOICE_HANDLE* playVoice(const ParamObj& obj, CV_FIELD field, CV_PRIO prio);
    static GAME_VOICE_HANDLE* playVoice(const ParamObj& obj, CV_FIELD field, unsigned int, unsigned int, CV_PRIO prio);
};
}  // namespace gf

#endif

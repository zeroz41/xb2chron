#ifndef GF_GFGAMEUTIL_H
#define GF_GFGAMEUTIL_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// game-wide helpers (functions, by its symbols)
class GfGameUtil {
public:
    // whether the object behind a handle is playing a voice
    static bool isPlayVoice(gf::GF_OBJ_HANDLE* handle);
};

}  // namespace gf

#endif

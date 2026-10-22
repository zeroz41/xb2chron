#ifndef GF_GFGAMEUTIL_H
#define GF_GFGAMEUTIL_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// game-wide helpers (functions, by its symbols)
class GfGameUtil {
public:
    // whether the object behind a handle is playing a voice
    static bool isPlayVoice(gf::GF_OBJ_HANDLE* handle);

    // the text the action window shows for an object (the names are not the original's)
    struct UiActionWindowInfo {
        UiActionWindowInfo() : m_bdat(nullptr), m_id(-1) {}
        void create(gf::GF_OBJ_HANDLE* handle);  // the text for the object behind the handle
        unsigned char* m_bdat;  // the message table and its id, as ui::UIStr takes them
        unsigned int m_id;
    };
};

}  // namespace gf

#endif

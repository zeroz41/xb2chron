#ifndef GF_GFGAMEUTIL_H
#define GF_GFGAMEUTIL_H

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { namespace mtl { template <int LEN> class FixStr; } }

namespace gf {

// game-wide helpers (functions, by its symbols)
class GfGameUtil {
public:
    // whether the object behind a handle is playing a voice
    static bool isPlayVoice(gf::GF_OBJ_HANDLE* handle);
    // the object takes field damage (GfGameScene::setDamageCharacter)
    static void requestFieldDamage(gf::GF_OBJ_HANDLE* handle);
    // the object's menu offset id, for GfMenuBdat::getMenuOffset
    static int getUiOffsetId(gf::GF_OBJ_HANDLE* handle);
    // the object a weapon object belongs to
    static gf::GF_OBJ_HANDLE* getWeaponOwner(gf::GF_OBJ_HANDLE* handle);
    // the name of a weapon's idle state for its owner, in battle or not
    static void makeWeaponStateIdle(mm::mtl::FixStr<32>& out, gf::GF_OBJ_HANDLE* owner, bool battle);

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

#ifndef CLASSES_GF_GFFIELDSOUND_H
#define CLASSES_GF_GFFIELDSOUND_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"

namespace gf { class GfFieldSound; }
namespace gf { class GfSetupParam; class MapjumpCallbackInfo; class GF_OBJ_HANDLE; enum GEV : int; enum RELOAD_BDAT : int; }
namespace gf { class GfFieldBgm; class GfFieldMapSe; class GF_SE_CATEGORY_HANDLE; }
namespace fw { class UpdateInfo; class SoundPack; class SoundResource; }

namespace gf {
// table 0x7100B525B8
class GfFieldSound : public ::mm::mtl::PtrSingleton< ::gf::GfFieldSound> {
public:
    // a sound pack loaded from a file: the resource it requests, the pack SoundManager finds for it, the file's path
    // and the pack's name (the map's SE pack at +0x30 and 3.0.1's DLC battle SE pack at +0x108 have this shape;
    // the class and field names are not the original's)
    class SoundInfo {
    public:
        SoundInfo() : m_resource(nullptr), m_pack(nullptr) {}
        // releases the resource and empties the strings (1.0.0's destroyMapSound did this for the map's)
        inline void destroy();
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because createMapSound calls
        // it on the SoundInfo at +0x108 (x0) and it fills that object's fields; inline (3.0.1 emits it after
        // createMapSound's other callees and its "sound/se/" literal last). What it does: destroy, then requests
        // "sound/se/<name>.xsp" (setup 3, 0, 0x80; priority 10), waits until it is valid and finds the pack <name>.
        inline void fn_710027CB9C(const char* name);

        fw::SoundResource* m_resource;
        fw::SoundPack* m_pack;
        mm::mtl::FixStr<128> m_path;
        mm::mtl::FixStr<64> m_name;
    };

    // 1.0.0's GfFieldSound(const GfSetupParam&) (3.0.1's build inlines it)
    GfFieldSound(const GfSetupParam& param)
        : m_isInitialized(false), m_bgm(nullptr), m_mapSe(nullptr), m_commonResource(nullptr),
          m_commonPack(nullptr), m_categoryHandle(reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1)),
          m_mapjumpCategoryHandle(reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1)),
          m_eventCategoryHandle(reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1)) {
        initialize(param);
    }
    virtual ~GfFieldSound();  // slot 0
    void initialize(const GfSetupParam& param);
    void finalize();
    // GfFieldManager's forwards (its initialize, finalize, clear, update, postUpdate and gev* functions call them)
    static void build(const GfSetupParam& param);
    static void destroy();
    // 1.0.0's createCommonSound (the symbol at the same place, called from the same place: initialize, with the
    // same body); 3.0.1 adds the DLC flag, which it stores in s_isDlc before picking the pack name
    void createCommonSound(bool isDlc);
    // 2.0.0's symbols name it. What it does: returns _gffsn::s_szDlcCommonName when s_isDlc is set, else
    // _gffsn::s_szCommonName ("dlc_fld_allmap" / "se_fld_allmap"; 1.0.0's GfFobjSeManager::create passes the literal
    // "se_fld_allmap" to SoundManager::findPack where 3.0.1 calls this); GfFobjSeManager::create and rebuildForGameType
    // pass it to SoundManager::findPack.
    static const char* getSePackName();
    void destroyCommonSound();
    void clear();
    void update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    void gevPlayEvent(GEV gev, unsigned int eventId);
    void gevBattleEnd();
    void gevGameMapModel(GF_OBJ_HANDLE* handle, bool flag);
    void gevMapjump(GEV gev, const MapjumpCallbackInfo& info);
    void gevPause(unsigned int flags0, unsigned int flags1);
    void createMapSound();
    // the full path of the map's SE file "se_fld_<name>" ("dlc_<name>" in the DLC game; 1.0.0's out-of-line
    // member, inline in 3.0.1's createMapSound)
    static inline void getMapSeFile(mm::mtl::FixStr<128>& path, const char* name);
    // 1.0.0's symbol at the same place, called from the same place (GfReqCommand::execMapjump)
    void destroyMapSound();
    void waitLoadMapSound();
    // the sound packs its +0x28 and +0x38 hold (GfFieldMapGimmick picks one by a row's "flag" bit)
    fw::SoundPack* getCommonPack();
    fw::SoundPack* getMapPack();
    // 2.0.0's symbols name it. What it does: the DLC battle SE pack (m_dlcSound's) when it holds a source of that name
    // (SoundPack::findSource), else null.
    fw::SoundPack* getDlcSePack(const char* name);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because fn_71002EE5C0 calls it
    // on GfFieldSound's instance (it then ignores this). What it does: maps "btl_spskill_001".."btl_spskill_004" to
    // "dlc_se_btl_bl40040116".."dlc_se_btl_bl40040119", null for any other name.
    const char* fn_710027CEA4(const char* name);
    void setCategorySeFadeoutForMapjump(float time);
    void setCategorySeFadeinForMapjump(float time);
    void destroyCategorySeForMapjump();

    bool m_isInitialized;  // initialize sets it, finalize clears it (the name is not the original's)
    GfFieldBgm* m_bgm;  // initialize creates it (the field names below are not the original's)
    GfFieldMapSe* m_mapSe;
    fw::SoundResource* m_commonResource;  // createCommonSound's
    fw::SoundPack* m_commonPack;
    SoundInfo m_mapSound;  // createMapSound's ("se_fld_<map>" or "dlc_<map>")
    SoundInfo m_dlcSound;  // createMapSound's "dlc_se_btl_spskill" when fn_71002ED330 holds
    GF_SE_CATEGORY_HANDLE* m_categoryHandle;
    GF_SE_CATEGORY_HANDLE* m_mapjumpCategoryHandle;  // the *ForMapjump fades use it
    GF_SE_CATEGORY_HANDLE* m_eventCategoryHandle;  // 1.0.0's setCategorySeFadeoutForEvent used it
};
}  // namespace gf

#endif

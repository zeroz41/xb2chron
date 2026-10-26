#ifndef CLASSES_GF_GFSOUND_H
#define CLASSES_GF_GFSOUND_H

#include "classes/gf/IGfEvent.h"
#include "classes/gf/GfManager.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedList.h"

#include "gf/SoundHandle.h"
#include "classes/fw/SoundManager.h"

namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace fw { enum SoundCategory : int; }
namespace gf { class GF_SE_CATEGORY_HANDLE; }
namespace gf { class GfSound; }
namespace gf { class SoundParam; }
namespace fw { class SoundPack; }

namespace gf {
// the master volumes GfSound applies to its categories (GfSound+0x6690; 1.0.0's setters name the volumes, in order)
class GfMasterVolume {
public:
    // out of line in 1.0.0 and 3.0.1 (fn_7100570CC8, which 3.0.1's SSoundUiOption::clear calls where 1.0.0's calls
    // GfMasterVolume::GfMasterVolume()); GfSound's constructor, in the same file, inlines it
    GfMasterVolume();
    ~GfMasterVolume();
    inline void initialize();  // a category handle of its own (1.0.0's GfMasterVolume::initialize)
    inline void initialize(const GfSetupParam& param);  // 1.0.0's GfSound::initialize, inline in 3.0.1's constructor
    inline void finalize();  // gives it back (1.0.0's GfMasterVolume::finalize)
    void setupGame();
    void setGameSeVolume(float volume);
    static int getU16Volume(float volume);

    GF_SE_CATEGORY_HANDLE* m_handle;
    float m_eventVoiceVolume;
    float m_eventCsVolume;
    float m_eventBgmVolume;
    float m_eventSeVolume;
    float m_gameBgmVolume;
    float m_gameEnvVolume;
    float m_gameWeatherVolume;
    float m_gameSeVolume;
    float m_playerVoiceVolume;
    float m_enemyVoiceVolume;
    float m_nareVoiceVolume;
    float m_systemVolume;
    float m_menuBgmVolume;
};

// table 0x7100B6B940
class GfSound : public ::mm::mtl::PtrSingleton< ::gf::GfSound>, public ::gf::IGfEvent {
public:
    // a volume reached over time (the names are not the original's)
    struct Volume {
        Volume() : current(1.0f), target(1.0f), start(1.0f), time(0.0f), timer(0.0f) {}
        void set(float volume, float fadeTime) {
            timer = fadeTime;
            time = fadeTime;
            start = current;
            target = volume;
        }
        float current;
        float target;
        float start;
        float time;
        float timer;
    };
    // one category handle's volumes, one per fw::SoundCategory (the field names are not the original's)
    class CategoryVolume {
    public:
        CategoryVolume();
        Volume m_volumes[18];
        int m_id;  // the constructor makes it -1
        bool m_isFree;  // the constructor makes it true
    };
    // a playing SE (1.0.0's GfSound::SeParam::clear: 0, -1, an empty SoundHandle; the names are not the original's)
    class SeParam {
    public:
        unsigned char pad_0;
        unsigned char m_kind;
        unsigned char pad_2;
        unsigned char m_pause;
        unsigned int pad_4;
        unsigned long pad_8;
        SoundHandle m_handle;
    };

    GfSound(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    inline void initialize(const GfSetupParam& param);  // 1.0.0's GfSound::initialize, inline in 3.0.1's constructor
    inline void finalize();  // 1.0.0's GfSound::finalize, inline in 3.0.1's destroy
    void update(const fw::UpdateInfo& info);
    void calcCategoryVolume(const fw::UpdateInfo& info);
    void updateSeParamList(const fw::UpdateInfo& info);
    virtual ~GfSound();  // slot 0
    void setupGame();
    virtual void gevPause(unsigned int, unsigned int);  // slot 2
    virtual void gevLayerPause(unsigned int, bool);  // slot 3
    void setCategoryPitch(fw::SoundCategory category, float pitch, float time);
    GF_SE_CATEGORY_HANDLE* createCategoryHandle();
    void releaseCategoryHandle(GF_SE_CATEGORY_HANDLE*& handle);
    // a category's volume under that handle, reached over time (GfMenuSoundManager's fades pass 1.0 or 0.0 and their
    // time)
    void setCategoryVolume(GF_SE_CATEGORY_HANDLE* handle, fw::SoundCategory category, float volume, float time);
    void destroyCategorySe(fw::SoundCategory category);  // GfFieldSound::destroyCategorySeForMapjump's
    float getCategoryVolume(GF_SE_CATEGORY_HANDLE* handle, fw::SoundCategory category) const;  // GfGameEvent's
    void stopBgm(SoundHandle handle, float time);  // TitleMain::stopTitleBGM passes its BGM and fade time
    SoundHandle playVoice(const char* path, float volume, bool loop, fw::SoundCategory category);
    void stopVoice(SoundHandle handle, float time);
    bool getPlayTime(SoundHandle handle, float& time) const;
    bool getTotalTime(SoundHandle handle, float& time) const;
    bool setPlayTime(SoundHandle handle, float time);
    void setPan(SoundHandle handle, float pan, float time);
    bool isPlaying(SoundHandle handle) const;
    bool isPreparing(SoundHandle handle) const;
    SoundHandle playSe(const SoundParam& param);
    void stopSe(SoundHandle handle, float time);
    void setVolume(SoundHandle handle, float volume, float time);
    float getVolume(SoundHandle handle);
    void setCategory(SoundHandle handle, fw::SoundCategory category);
    // the playing SE of index, null for none (1.0.0's GfSound::getSeParam(unsigned short), inline in 3.0.1)
    SeParam* getSeParam(unsigned short index) {
        if (index == 0xFFFF) {
            return nullptr;
        }
        return &m_seParams[index];
    }

    // sets or clears type in the SE's pause bits and pauses or resumes it when that changes whether it is paused
    // (1.0.0's GfSound::setPauseType, inline in 3.0.1)
    void setPauseType(SoundHandle handle, bool pause, float time, unsigned char type) {
        if (SeParam* param = getSeParam(handle.m_seIndex)) {
            unsigned char prev = param->m_pause;
            if (pause) {
                param->m_pause |= type;
            } else {
                param->m_pause &= ~type;
            }
            if ((prev == 0) != (param->m_pause == 0)) {
                if (fw::SoundManager* manager = fw::SoundManager::get()) {
                    manager->pause(handle.m_id, pause, time);
                }
            }
        }
    }
    // gives the SE of index back (1.0.0's GfSound::deAllocateSeParam, inline in 3.0.1)
    void deAllocateSeParam(unsigned short index) {
        if (index != 0xFFFF) {
            m_seParams.free(index);
        }
    }
    void setPause(SoundHandle handle, bool pause, float time);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this GfSound's
    // SeParams (this+0x5268) like setPause next to it. What it does: 1.0.0's setPauseType with type 8 (sets or
    // clears pause bit 3 of the handle's SE and calls fw::SoundManager::pause when its paused state changes).
    void fn_7100570158(SoundHandle handle, bool pause, float time);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason. What it does:
    // whether the handle's SE has pause bit 3 set (false when the handle has no SE).
    bool fn_71005701D8(SoundHandle handle);
    void setPauseGameSe(bool pause);
    void setPauseGameWeatherSe(bool pause);
    void setPauseEventSe(bool pause);
    void destroyObjSePack(fw::SoundPack*& pack);

    // the field names are not the original's
    bool m_isEnable;  // the constructor's last store, destroy clears it
    bool m_isVolumeDirty;  // update clears it after calcCategoryVolume
    unsigned long pad_18;
    mm::mtl::FixedArray<CategoryVolume, 32> m_categoryVolumes;  // by category handle
    ml::fixed_size_alloc_inside<SeParam, 384> m_seParams;
    mm::mtl::FixedList<unsigned short, 512> m_seList;  // indices into m_seParams
    GfMasterVolume m_masterVolume;
    GF_SE_CATEGORY_HANDLE* m_categoryHandle;
};
}  // namespace gf

#endif

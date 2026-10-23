#ifndef CLASSES_GF_GFSOUND_H
#define CLASSES_GF_GFSOUND_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

#include "gf/SoundHandle.h"

namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace fw { enum SoundCategory : int; }
namespace gf { class GF_SE_CATEGORY_HANDLE; }
namespace gf { class GfSound; }
namespace gf { class SoundParam; }

namespace gf {
// table 0x7100B6B940
class GfSound : public ::mm::mtl::PtrSingleton< ::gf::GfSound>, public ::gf::IGfEvent {
public:
    static void build(const GfSetupParam& param);
    static void destroy();
    void update(const fw::UpdateInfo& info);
    class SeParam;
    virtual ~GfSound();  // slot 0
    void setupGame();
    virtual void gevPause(unsigned int, unsigned int);  // slot 2
    virtual void gevLayerPause(unsigned int, bool);  // slot 3
    void setCategoryPitch(fw::SoundCategory category, float pitch, float time);  // fw::SoundManager's, if there is one
    GF_SE_CATEGORY_HANDLE* createCategoryHandle();
    void releaseCategoryHandle(GF_SE_CATEGORY_HANDLE*& handle);
    // a category's volume under that handle, reached over time (GfMenuSoundManager's fades pass 1.0 or 0.0 and their
    // time)
    void setCategoryVolume(GF_SE_CATEGORY_HANDLE* handle, fw::SoundCategory category, float volume, float time);
    SoundHandle playVoice(const char* path, float volume, bool loop, fw::SoundCategory category);
    bool getPlayTime(SoundHandle handle, float& time) const;
    bool isPlaying(SoundHandle handle) const;
    SoundHandle playSe(const SoundParam& param);
    void stopSe(SoundHandle handle, float time);
    void setVolume(SoundHandle handle, float volume, float time);
};
}  // namespace gf

#endif

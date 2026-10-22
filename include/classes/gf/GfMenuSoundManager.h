#ifndef CLASSES_GF_GFMENUSOUNDMANAGER_H
#define CLASSES_GF_GFMENUSOUNDMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfSound.h"
#include "gf/SoundHandle.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfMenuSoundManager; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B5F070; the jingles the menus play over the field BGM, which it turns down while one plays
class GfMenuSoundManager : public ::mm::mtl::PtrSingleton< ::gf::GfMenuSoundManager> {
public:
    // a playing jingle (0xC bytes)
    class JingleInfo {
    public:
        JingleInfo() : m_handle(0) {}
        SoundHandle m_handle;  // GfSound::playVoice's; the name is not the original's
        unsigned int m_id;  // playJingle's; its row in BDAT 0x188; the name is not the original's
    };

    // build constructs it (1.0.0 has no constructor of its own)
    GfMenuSoundManager() : m_initialized(true), m_categoryHandle(reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1)) {
        if (GfSound* sound = GfSound::get()) {
            m_categoryHandle = sound->createCategoryHandle();
            m_jingles.clear();
        }
    }
    virtual ~GfMenuSoundManager();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isInitialized();
    static void postUpdate(const fw::UpdateInfo& info);
    static void fadeInFieldBgm(float time);
    static SoundHandle playJingle(unsigned int id);
    static void fadeFieldBgm(float time, float volume);
    static void fadeOutFieldBgm(float time);

    bool m_initialized;  // what isInitialized returns: set by build, cleared by destroy; the name is not the original's
    mm::mtl::FixedVector<JingleInfo, 8> m_jingles;  // playJingle's, until they end; the name is not the original's
    GF_SE_CATEGORY_HANDLE* m_categoryHandle;  // GfSound::createCategoryHandle's; the name is not the original's
};
}  // namespace gf

#endif

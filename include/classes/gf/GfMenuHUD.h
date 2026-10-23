#ifndef CLASSES_GF_GFMENUHUD_H
#define CLASSES_GF_GFMENUHUD_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfMenuHUD; }
namespace gf { class GfSetupParam; }
namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5E890
class GfMenuHUD : public ::mm::mtl::PtrSingleton< ::gf::GfMenuHUD> {
public:
    // a UI object the HUD waits for (fn_7100353A04 asks UIManager::searchObject for each); the names are not the
    // original's
    struct WaitObject {
        const char* m_name;
        unsigned int m_id;
    };
    virtual ~GfMenuHUD();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isInitialized();
    static void postUpdate(const fw::UpdateInfo& info);
    static void reciveUIEvent(const ui::EventData& event, unsigned int handle);
    // 1.0.0's: the scenes back to 0 (3.0.1 has no copy: destroy inlines it)
    void finalize() {
        m_sceneId = 0;
        m_nextSceneId = 0;
    }
    // the system sequence postUpdate runs: start, wait, update
    void systemStart();
    void systemWait();
    void systemUpdate();
    bool m_initialized;
    unsigned int m_sceneId;      // 1.0.0's getSceneID reads it (the name is not the original's)
    unsigned int m_nextSceneId;  // 1.0.0's changeScene sets it (the name is not the original's)
    unsigned char pad_14[4];
    // cleared by the destructor; what it holds is not known yet (0x20 bytes of room, the element type is a guess)
    mm::mtl::FixedVector<unsigned long, 4> m_list18;
    mm::mtl::Delegate<void()> m_system;  // the system sequence's step (systemStart, systemWait, systemUpdate)
    mm::mtl::Delegate<void()> m_scene;   // the scene sequence's step (1.0.0's sceneChangeStart and the rest)
    unsigned int m_layerType;  // the menu layers initialize creates (3 for one game mode); the name is not the original's
    unsigned char pad_84[4];
    mm::mtl::FixedVector<WaitObject, 64> m_waitObjects;  // the name is not the original's
};
}  // namespace gf

#endif

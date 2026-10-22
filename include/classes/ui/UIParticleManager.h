#ifndef CLASSES_UI_UIPARTICLEMANAGER_H
#define CLASSES_UI_UIPARTICLEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ui/UIParticleEmitter.h"
#include "mm/mtl/IntrusiveList.h"

namespace ui { class UIParticleManager; }
namespace ui { class UIParticleData; }
namespace fw { class UpdateInfo; }
namespace mm { template <typename> class Pnt; }

namespace ui {
// table 0x7100B74FF8; the emitters it runs, each under the handle create gave it
class UIParticleManager : public ::mm::mtl::PtrSingleton< ::ui::UIParticleManager> {
public:
    // one emitter in the list (the name is not the original's)
    struct EmitterNode : public mm::mtl::IntrusiveListNodeBase {
        ~EmitterNode() {
            if (m_emitter != nullptr) {
                delete m_emitter;
                m_emitter = nullptr;
            }
        }
        int m_handle;                  // create's
        float m_weight;                // how much of the load reduction applies to it (create: all)
        UIParticleEmitter* m_emitter;  // it deletes it
    };
    UIParticleManager();
    virtual ~UIParticleManager();  // slot 0
    void update(const fw::UpdateInfo& info);
    int create(const UIParticleData& data);  // the emitter's handle, -1 when none is made
    void remove(int handle);
    UIParticleEmitter* getEmitter(int handle);
    void setEmitterPos(int handle, const mm::Pnt<short>& pos);
    void setEmitterRot(int handle, float rot);
    mm::mtl::IntrusiveList<EmitterNode> m_emitters;
    int m_nextHandle;       // the next emitter's handle (from 1)
    float m_loadReduction;  // 1.0.0's setLoadReduction: the share of the emitters' rate taken away
};
}  // namespace ui

#endif

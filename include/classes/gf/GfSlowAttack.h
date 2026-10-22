#ifndef CLASSES_GF_GFSLOWATTACK_H
#define CLASSES_GF_GFSLOWATTACK_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }

namespace gf { class GfSlowAttack; }

namespace gf {
// table 0x7100B55FB0
class GfSlowAttack : public ::mm::mtl::PtrSingleton< ::gf::GfSlowAttack> {
public:
    // inline: create is the only constructor call, and no out-of-line copy exists
    GfSlowAttack() {
        m_execute = false;
        m_update.set(this, &GfSlowAttack::updateForIdle);
        m_state = 0;
    }
    virtual ~GfSlowAttack();  // slot 0
    void updateForIdle(const fw::UpdateInfo& info);
    void updateForPlay(const fw::UpdateInfo& info);
    void updateForTerm(const fw::UpdateInfo& info);
    void update(const fw::UpdateInfo& info);
    static GfSlowAttack* create();
    static void destroy();
    void executeSlow();

    int m_state;  // 0 idle, 1 playing, 2 ending: set beside the update it selects
    mm::mtl::Delegate<void(const fw::UpdateInfo&)> m_update;  // updateForIdle, updateForPlay or updateForTerm
    bool m_execute;  // set by executeSlow; update clears it after the state's update has seen it
};
}  // namespace gf

#endif

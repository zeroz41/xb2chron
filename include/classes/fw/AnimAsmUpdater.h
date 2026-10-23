#ifndef CLASSES_FW_ANIMASMUPDATER_H
#define CLASSES_FW_ANIMASMUPDATER_H

#include "classes/fw/AnimControlUpdater.h"

namespace anm { class ASMControl; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B40BC0: updates one anm::ASMControl it references (AnimationManager::addControlUpdater keeps it)
class AnimAsmUpdater : public ::fw::AnimControlUpdaterInterface {
public:
    AnimAsmUpdater();
    virtual ~AnimAsmUpdater();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    void bind(anm::ASMControl* control);
    void unbind();
    // whether a control is bound (inline: the name is not the original's)
    bool isBind() const { return m_control != nullptr; }

    anm::ASMControl* m_control;  // bind's
};
}  // namespace fw

#endif

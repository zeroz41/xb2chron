#ifndef CLASSES_FW_ANIMCONTROLUPDATER_H
#define CLASSES_FW_ANIMCONTROLUPDATER_H

#include "mm/mtl/IntrusiveList.h"

namespace anm { class Control; }
namespace fw { class UpdateInfo; }

namespace fw {
// what AnimationManager::addControlUpdater/removeControlUpdater keep (AnimControlUpdater is one, at its start)
class AnimControlUpdaterInterface {
public:
    virtual ~AnimControlUpdaterInterface() {}
    virtual void update(fw::UpdateInfo const&) = 0;
};

// table 0x7100B40B70: updates one anm::Control it references
class AnimControlUpdater : public ::fw::AnimControlUpdaterInterface {
public:
    AnimControlUpdater();
    virtual ~AnimControlUpdater();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    void bind(anm::Control* control);
    void unbind();
    // whether a control is bound (inline: the name is not the original's)
    bool isBind() const { return m_control != nullptr; }

    mm::mtl::IntrusiveListNodeBase m_node;  // the constructor links it to itself
    anm::Control* m_control;  // bind references it, unbind releases it
};
}  // namespace fw

#endif

#ifndef CLASSES_FW_ANIMBLENDERUPDATER_H
#define CLASSES_FW_ANIMBLENDERUPDATER_H

#include "classes/fw/AnimControlUpdater.h"
namespace anm { class Blender; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B40B98: updates one anm::Blender it references (GfComEvtAnim::Mot's)
class AnimBlenderUpdater : public ::fw::AnimControlUpdaterInterface {
public:
    AnimBlenderUpdater();
    virtual ~AnimBlenderUpdater();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    void bind(anm::Blender* blender);
    void unbind();

    anm::Blender* m_blender;  // bind's (GfComEvtAnim::changeLayer tests it; the name is not the original's)
};
}  // namespace fw

#endif

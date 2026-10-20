#ifndef CLASSES_FW_ANIMCONTROLUPDATER_H
#define CLASSES_FW_ANIMCONTROLUPDATER_H

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B40B70
class AnimControlUpdater {
public:
    virtual ~AnimControlUpdater();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace fw

#endif

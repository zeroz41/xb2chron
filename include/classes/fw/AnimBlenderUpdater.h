#ifndef CLASSES_FW_ANIMBLENDERUPDATER_H
#define CLASSES_FW_ANIMBLENDERUPDATER_H

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B40B98
class AnimBlenderUpdater {
public:
    virtual ~AnimBlenderUpdater();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace fw

#endif

#ifndef CLASSES_FW_ANIMASMUPDATER_H
#define CLASSES_FW_ANIMASMUPDATER_H

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B40BC0
class AnimAsmUpdater {
public:
    virtual ~AnimAsmUpdater();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace fw

#endif

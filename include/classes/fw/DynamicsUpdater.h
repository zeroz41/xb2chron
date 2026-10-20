#ifndef CLASSES_FW_DYNAMICSUPDATER_H
#define CLASSES_FW_DYNAMICSUPDATER_H

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B412C8
class DynamicsUpdater {
public:
    virtual ~DynamicsUpdater();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void drawDebug();  // slot 3
};
}  // namespace fw

#endif

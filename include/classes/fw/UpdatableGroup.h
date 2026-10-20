#ifndef CLASSES_FW_UPDATABLEGROUP_H
#define CLASSES_FW_UPDATABLEGROUP_H

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B424A0
class UpdatableGroup {
public:
    virtual ~UpdatableGroup();  // slot 0
    virtual void update(fw::UpdateInfo const&, unsigned int);  // slot 2
    virtual void tail(fw::UpdateInfo const&);  // slot 3
};
}  // namespace fw

#endif

#ifndef CLASSES_FW_EFFECTCASTERBASE_H
#define CLASSES_FW_EFFECTCASTERBASE_H

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41320
class EffectCasterBase {
public:
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 0
    virtual void postUpdate(fw::UpdateInfo const&) = 0;  // slot 1
    virtual ~EffectCasterBase();  // slot 2
};
}  // namespace fw

#endif

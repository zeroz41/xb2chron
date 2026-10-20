#ifndef CLASSES_GF_EFFECTCASTER_H
#define CLASSES_GF_EFFECTCASTER_H

#include "classes/fw/EffectCasterBase.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B65AF8
class EffectCaster : public ::fw::EffectCasterBase {
public:
    virtual void update(fw::UpdateInfo const&);  // slot 0
    virtual void postUpdate(fw::UpdateInfo const&);  // slot 1
    virtual ~EffectCaster();  // slot 2
};
}  // namespace gf

#endif

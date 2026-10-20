#ifndef CLASSES_GF_GFCOMBEHAVIORUI_H
#define CLASSES_GF_GFCOMBEHAVIORUI_H

#include "classes/gf/GfComBehavior.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B69D78
class GfComBehaviorUI : public ::gf::GfComBehavior {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComBehaviorUI();  // slot 1
    virtual void update(fw::UpdateInfo const&);  // slot 5
};
}  // namespace gf

#endif

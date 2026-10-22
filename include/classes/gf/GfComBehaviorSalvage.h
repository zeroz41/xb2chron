#ifndef CLASSES_GF_GFCOMBEHAVIORSALVAGE_H
#define CLASSES_GF_GFCOMBEHAVIORSALVAGE_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/Delegate.h"
#include "classes/gf/GfComBehavior.h"

namespace fw { class UpdateInfo; }
namespace gf { class CallBackCache; }
namespace gf { class GfComAsm; }

namespace gf {
// table 0x7100B69C68
class GfComBehaviorSalvage : public ::gf::GfComBehavior {
public:
    GfComBehaviorSalvage();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehaviorSalvage();  // slot 1
    virtual void update(fw::UpdateInfo const&);  // slot 5
    virtual void procAnimCallback(gf::GfComAsm*, gf::CallBackCache const&);  // slot 6
    void setup();
    void cleanup();
    static mm::mtl::RTTI m_rtti;

    // called on the salvage animation's "salvageStep" and "vibration" events
    mm::mtl::Delegate<void()> m_stepCallback;
};
}  // namespace gf

#endif

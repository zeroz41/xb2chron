#ifndef CLASSES_ANM_CONTROL_H
#define CLASSES_ANM_CONTROL_H

#include "classes/anm/ReferenceObject.h"
#include "mm/mtl/Vector.h"

namespace anm { class Binding; }
namespace anm { class QsTransform; }

namespace anm {
// table 0x7100B81138; plays a binding's animation: its local time, advanced by update
class Control : public ::anm::ReferenceObject {
public:
    Control(const Binding* pBinding, mm::mtl::IAllocator* pAllocator);
    virtual ~Control();  // slot 0
    // advances the local time by dt at the speed, wrapped (or clamped) to the animation's length
    void update(float dt);
    float calcLocalTimeInternal(float time);
    // the local time set to time, wrapped (or clamped) like update's, and flagged (inline: AsmClip::setLocalTime and
    // AsmClip::update; the name is not the original's)
    void setLocalTime(float time) {
        m_localTime = calcLocalTimeInternal(time);
        m_flags |= 1;
    }
    // the binding's animation sampled at the local time: one transform per entry of its index table
    void sampleTrucks(unsigned int count, QsTransform* pOut) const;
    // the extra-track slot's values at the local time: false when it has none, or not count of them
    bool sampleExtraTrucks(unsigned short slot, unsigned int count, float* pOut);

    const Binding* m_pBinding;  // anm_control.cpp asserts `pBinding` and `m_pBinding`
    // per entry of the binding's index table, 1 (0 for an entry without a track); the names of these fields are
    // not the original's
    mm::mtl::Vector<float> m_trackWeights;
    float m_localTime;  // update advances it; the samplers sample at it
    float m_weight;     // the constructor's 1
    float m_speed;      // update scales its time step by it; the constructor's 1
    float m_length;     // the animation's: its frame interval times its frame count less one
    unsigned int m_flags;  // bit 0: the local time was set (setLocalTime); the constructor's 0. The name is not the original's
    void* pad_60;
};
}  // namespace anm

#endif

#ifndef CLASSES_ANM_ANIMATION_H
#define CLASSES_ANM_ANIMATION_H

#include "anm/AnimationObject.h"

namespace anm { class Binding; }
namespace anm { class Locomotion; }
namespace anm { class QsTransform; }

namespace anm {
// table none (its derived classes')
class Animation : public ::anm::AnimationObject {
public:
    // trivial and inline: a derived class's slot holds AnimationObject's
    virtual ~Animation() {}  // slot 0
    virtual int getImplType() const = 0;  // slot 2: which kind (the type is not the original's)
    virtual void sampleTrucks(float, anm::Binding const&, anm::QsTransform*) const = 0;  // slot 3
    virtual void getExtractMotion(float, anm::QsTransform*) const;  // slot 4
    virtual void getDeltaExtractMotion(float, float, bool, anm::QsTransform*) const;  // slot 5

    unsigned char pad_8[0x10];
    const char* m_name;  // 1.0.0's Control::getName returns it
    unsigned char pad_20;
    // Factory::createMirrorAnimation mirrors no animation where it is 1 (the name is not the original's)
    unsigned char m_noMirror;
    bool m_clampTime;  // anm::Control clamps its local time to the length while set, wraps it when not (the name
                       // is not the original's)
    unsigned char pad_23[0x5];
    float m_interval;           // the time between two frames (1.0.0's getDeltaExtractMotion; the name is not the
                                // original's)
    unsigned int m_frameCount;  // the length is m_interval times one less than it
    unsigned char pad_30[0x10];
    const Locomotion* m_pLocomotion;  // 1.0.0's getDeltaExtractMotion reads it when set
};
}  // namespace anm

#endif

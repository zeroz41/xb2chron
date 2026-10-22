#ifndef CLASSES_ANM_ANIMATION_H
#define CLASSES_ANM_ANIMATION_H

#include "anm/AnimationObject.h"
#include "anm/Locomotion.h"

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
    // inline: Animation has no table of its own, and the copy the linker kept lies in anm_cubic_animation.cpp's
    // range. True with the locomotion's reference at time, false with no locomotion
    virtual bool getExtractMotion(float time, anm::QsTransform* pOut) const {  // slot 4
        if (m_pLocomotion != nullptr) {
            m_pLocomotion->getReference(time, pOut);
            return true;
        }
        return false;
    }
    // the locomotion's motion from time to time + delta over the whole animation, wrapping around when loop
    virtual bool getDeltaExtractMotion(float time, float delta, bool loop, anm::QsTransform* pOut) const {  // slot 5
        if (m_pLocomotion != nullptr) {
            m_pLocomotion->getDeltaReference(time, delta, 0.0f, m_interval * (m_frameCount - 1), loop, pOut);
            return true;
        }
        return false;
    }

    const char* m_name;  // 1.0.0's Control::getName returns it
    unsigned char pad_20;
    // Factory::createMirrorAnimation mirrors no animation where it is 1 (the name is not the original's)
    unsigned char m_noMirror;
    bool m_clampTime;  // anm::Control clamps its local time to the length while set, wraps it when not (the name
                       // is not the original's)
    unsigned char pad_23;
    float m_frameRate;  // frames per second: a time's frame is it times the time (UncompressAnimation::sampleTrucks; the
                        // name is not the original's)
    float m_interval;           // the time between two frames (1.0.0's getDeltaExtractMotion; the name is not the
                                // original's)
    unsigned int m_frameCount;  // the length is m_interval times one less than it
    unsigned char pad_30[0x10];
    const Locomotion* m_pLocomotion;  // 1.0.0's getDeltaExtractMotion reads it when set
};
}  // namespace anm

#endif

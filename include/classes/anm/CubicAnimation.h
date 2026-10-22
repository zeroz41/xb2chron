#ifndef CLASSES_ANM_CUBICANIMATION_H
#define CLASSES_ANM_CUBICANIMATION_H

#include "anm/Array.h"
#include "anm/CubicCurve.h"
#include "classes/anm/Animation.h"

namespace anm { class Binding; }
namespace anm { class QsTransform; }

namespace anm { class SerialiseArg; }

namespace anm {
// one track of a CubicAnimation: its translation's, rotation's and scale's keys (the names are not the original's)
struct CubicTrack {
    Array<Cubic3Curve> m_translation;
    Array<Cubic4Curve> m_rotation;
    Array<Cubic3Curve> m_scale;
};

// table 0x7100B811D8; an animation kept as cubic keys per track
class CubicAnimation : public ::anm::Animation {
public:
    CubicAnimation(const SerialiseArg& arg);

    virtual ~CubicAnimation() {}  // slot 0
    virtual int getImplType() const;  // slot 2
    virtual void sampleTrucks(float, anm::Binding const&, anm::QsTransform*) const;  // slot 3

    // per track the binding's index table points at (the name is not the original's)
    Array<CubicTrack> m_tracks;
};
}  // namespace anm

#endif

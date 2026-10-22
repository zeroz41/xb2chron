#ifndef CLASSES_ANM_CUBICEXTRATRUCK_H
#define CLASSES_ANM_CUBICEXTRATRUCK_H

#include "anm/Array.h"
#include "anm/CubicCurve.h"
#include "anm/ExtraTruck.h"

namespace anm { class Binding; }
namespace anm { class ExtraBinding; }
namespace anm { class SerialiseArg; }

namespace anm {
// table 0x7100B81358
class CubicExtraTruck : public ::anm::ExtraTruck {
public:
    CubicExtraTruck(const SerialiseArg&) {}

    virtual void sampleTrucks(float, anm::Binding const&, anm::ExtraBinding const&, unsigned int, float*) const;  // slot 0

    // per value of the track, its keys (sampleTrucks; the name is not the original's)
    Array<Array<CubicCurve> > m_curves;
};
}  // namespace anm

#endif

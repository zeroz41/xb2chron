#ifndef CLASSES_ANM_CUBICEXTRATRUCK_H
#define CLASSES_ANM_CUBICEXTRATRUCK_H

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
};
}  // namespace anm

#endif

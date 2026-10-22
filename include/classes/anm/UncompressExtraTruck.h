#ifndef CLASSES_ANM_UNCOMPRESSEXTRATRUCK_H
#define CLASSES_ANM_UNCOMPRESSEXTRATRUCK_H

#include "anm/Array.h"
#include "anm/ExtraTruck.h"

namespace anm { class Binding; }
namespace anm { class ExtraBinding; }
namespace anm { class SerialiseArg; }

namespace anm {
// table 0x7100B81370
class UncompressExtraTruck : public ::anm::ExtraTruck {
public:
    UncompressExtraTruck(const SerialiseArg&) {}

    virtual void sampleTrucks(float, anm::Binding const&, anm::ExtraBinding const&, unsigned int, float*) const;  // slot 0

    // every frame's values, a frame's in a row (sampleTrucks; the name is not the original's)
    Array<float> m_values;
};
}  // namespace anm

#endif

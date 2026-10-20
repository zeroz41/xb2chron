#ifndef CLASSES_ANM_UNCOMPRESSEXTRATRUCK_H
#define CLASSES_ANM_UNCOMPRESSEXTRATRUCK_H

namespace anm { class Binding; }
namespace anm { class ExtraBinding; }

namespace anm {
// table 0x7100B81370
class UncompressExtraTruck {
public:
    virtual void sampleTrucks(float, anm::Binding const&, anm::ExtraBinding const&, unsigned int, float*) const;  // slot 0
};
}  // namespace anm

#endif

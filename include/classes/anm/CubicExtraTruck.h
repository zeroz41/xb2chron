#ifndef CLASSES_ANM_CUBICEXTRATRUCK_H
#define CLASSES_ANM_CUBICEXTRATRUCK_H

namespace anm { class Binding; }
namespace anm { class ExtraBinding; }

namespace anm {
// table 0x7100B81358
class CubicExtraTruck {
public:
    virtual void sampleTrucks(float, anm::Binding const&, anm::ExtraBinding const&, unsigned int, float*) const;  // slot 0
};
}  // namespace anm

#endif

#ifndef ANM_EXTRATRUCK_H
#define ANM_EXTRATRUCK_H

namespace anm { class Binding; }
namespace anm { class ExtraBinding; }

namespace anm {
// the common base of an animation's extra (non-bone) tracks, sampled through slot 0 (anm::Control::sampleExtraTrucks
// calls it on an ExtraBinding's track); abstract, so it has no table of its own. The class's and its fields'
// names are not the original's
class ExtraTruck {
public:
    virtual void sampleTrucks(float time, const Binding& binding, const ExtraBinding& extra, unsigned int count,
                              float* pOut) const = 0;  // slot 0

    unsigned char pad_8[0x8];
    unsigned char m_type;  // which kind: 0 UncompressExtraTruck, 1 CubicExtraTruck (ExtraBinding's constructor)
    unsigned char pad_11[0x7];
};
}  // namespace anm

#endif

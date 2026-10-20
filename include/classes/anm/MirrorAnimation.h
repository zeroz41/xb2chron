#ifndef CLASSES_ANM_MIRRORANIMATION_H
#define CLASSES_ANM_MIRRORANIMATION_H

namespace anm { class Binding; }
namespace anm { class QsTransform; }

namespace anm {
// table 0x7100B81258
class MirrorAnimation {
public:
    virtual ~MirrorAnimation();  // slot 0
    virtual void getImplType() const;  // slot 2
    virtual void sampleTrucks(float, anm::Binding const&, anm::QsTransform*) const;  // slot 3
    virtual void getExtractMotion(float, anm::QsTransform*) const;  // slot 4
    virtual void getDeltaExtractMotion(float, float, bool, anm::QsTransform*) const;  // slot 5
};
}  // namespace anm

#endif

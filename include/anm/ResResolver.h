#ifndef ANM_RESRESOLVER_H
#define ANM_RESRESOLVER_H

namespace anm { class Binding; }
namespace anm { class MirrorMapper; }
namespace anm { class SimpleMapper; }
namespace anm { class Skeleton; }

namespace anm {
// table none (pure); what an animation state machine resource's clips are bound with: ResASM's constructor takes its
// skeleton, ResClipData::setup each clip's binding and the mappers it retargets and mirrors with. The slots' names
// are fw::AnimResAsmResolver's (table 0x7100B40D70), which implements it; no slot is a destructor.
class ResResolver {
public:
    // the binding of a clip's animation (ResClipInfo's name and number)
    virtual const Binding* importBinding(const char* name, unsigned int index) const = 0;  // slot 0
    // the binding's binary back as it was loaded (AnimationImporter::restore's result)
    virtual bool restoreBinding(const char* name, unsigned int index) const = 0;  // slot 1
    virtual const Skeleton* getSkekelton() const = 0;  // slot 2 (the original spells it so)
    virtual const MirrorMapper* getMirrorMapper() const = 0;  // slot 3
    virtual const SimpleMapper* getSimpleMapper() const = 0;  // slot 4
};
}  // namespace anm

#endif

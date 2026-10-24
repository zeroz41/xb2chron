#ifndef CLASSES_ANM_ASMCONTROL_H
#define CLASSES_ANM_ASMCONTROL_H

#include "anm/QsTransform.h"
#include "anm/StateMachine.h"
#include "classes/anm/ReferenceObject.h"
#include "anm/AsmBlender.h"

namespace anm { class AsmListener; }
namespace anm { class ResASM; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// table 0x7100B81178; plays an animation state machine resource
class ASMControl : public ::anm::ReferenceObject {
public:
    ASMControl(const ResASM& res, mm::mtl::IAllocator& allocator);
    virtual ~ASMControl();  // slot 0
    void setListener(AsmListener* listener);
    void setVariable(const char* name, float value);
    void setVariable(const char* name, int value);
    void getVariable(const char* name, float* value) const;
    // the blender's sampling, forwarded (inline: the fw ASM pose samplers compute the blender's address after
    // their arguments; the names are not the original's)
    void sampleTrucks(unsigned int count, QsTransform* pOut) { m_blender.sampleTrucks(count, pOut); }
    void sampleTrucksMS(unsigned int count, QsTransform* pOut) { m_blender.sampleTrucksMS(count, pOut); }
    void sampleExtraTrucks(unsigned short slot, unsigned int count, float* pOut) {
        m_blender.sampleExtraTrucks(slot, count, pOut);
    }

    // the names of the fields are not the original's
    const ResASM* m_pRes;  // the constructor's
    // what the pose samplers sample (AsmBlender::sampleTrucks with this at 0x20; the name is not the original's)
    AsmBlender m_blender;
    unsigned char pad_48[0x28];
    StateMachine m_stateMachines[7];  // one per layer, each set up by the constructor
    QsTransform m_locomotion;
};
}  // namespace anm

#endif

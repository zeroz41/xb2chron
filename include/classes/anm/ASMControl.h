#ifndef CLASSES_ANM_ASMCONTROL_H
#define CLASSES_ANM_ASMCONTROL_H

#include "anm/QsTransform.h"
#include "../../anm/StateMachine.h"  // (anm/StateMachine.h once in the tree)
#include "classes/anm/ReferenceObject.h"

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

    // the names of the fields are not the original's
    const ResASM* m_pRes;  // the constructor's
    unsigned char pad_20[0x50];
    StateMachine m_stateMachines[7];  // one per layer, each set up by the constructor
    QsTransform m_locomotion;
};
}  // namespace anm

#endif

#ifndef ANM_ASMVARIABLE_H
#define ANM_ASMVARIABLE_H

#include "mm/mtl/Vector.h"

namespace anm {
// a variable's type (LerpBlendTree asserts `m_pVariable->getVarType() == VAR_FLOAT`, unqualified)
enum VarType {
    VAR_INT = 0,  // the name is not the original's
    VAR_FLOAT = 1,
};

// a variable's resource: its type and name (the rest is not known; the names are not the original's)
struct ResVariable {
    int m_type;  // a VarType
    const char* m_name;  // Variable::getName's; findVariable looks a variable up by it
};

// a variable of an animation state machine (ASMControl::setVariable/getVariable by name), 0x10 bytes: its resource
// and value (anm_asm_variable.cpp; getValue asserts `m_pResVariable`)
class Variable {
public:
    Variable();
    // the resource's, and a value to start from: 1 for an int variable, 0 for a float one
    void setup(const ResVariable& res);
    VarType getVarType() const { return static_cast<VarType>(m_pResVariable->m_type); }
    // the value of an int (or a float) variable; false for another type
    bool setValue(int value);
    bool setValue(float value);
    bool getValue(int* pValue) const;
    bool getValue(float* pValue) const;
    // the resource's name; "" without a resource (1.0.0's is out of line)
    const char* getName() const;

    const ResVariable* m_pResVariable;
    union {
        int m_intValue;  // the names are not the original's
        float m_floatValue;
    };
};

// the variable of the name among variables sorted by name (ASMControl::setVariable/getVariable); null for none
Variable* findVariable(mm::mtl::Vector<Variable>& variables, const char* name);
const Variable* findVariable(const mm::mtl::Vector<Variable>& variables, const char* name);
}  // namespace anm

#endif

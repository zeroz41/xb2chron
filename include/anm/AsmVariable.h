#ifndef ANM_ASMVARIABLE_H
#define ANM_ASMVARIABLE_H

namespace anm {
// a variable's type (LerpBlendTree asserts `m_pVariable->getVarType() == VAR_FLOAT`, unqualified)
enum VarType {
    VAR_INT = 0,  // the name is not the original's
    VAR_FLOAT = 1,
};

// a variable's resource: its type first (the rest is not known; the names are not the original's)
struct ResVariable {
    int m_type;  // a VarType
};

// a variable of an animation state machine (ASMControl::setVariable/getVariable by name), 0x10 bytes: its resource
// and value (anm_asm_variable.cpp; getValue asserts `m_pResVariable`)
class Variable {
public:
    Variable();
    VarType getVarType() const { return static_cast<VarType>(m_pResVariable->m_type); }
    // the value of a float variable; false for another type
    bool getValue(float* pValue) const;

    const ResVariable* m_pResVariable;
    union {
        int m_intValue;  // the names are not the original's
        float m_floatValue;
    };
};
}  // namespace anm

#endif

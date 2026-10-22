#include "anm/AsmVariable.h"

#include <algorithm>

#include "mm/MMStdBase.h"
#include "string.h"

namespace anm {

Variable::Variable() : m_pResVariable(nullptr) {}

void Variable::setup(const ResVariable& res) {
    m_pResVariable = &res;
    if (getVarType() == VAR_INT) {
        m_intValue = 1;
    } else {
        m_floatValue = 0.0f;
    }
}

bool Variable::setValue(int value) {
#line 52
    MM_ASSERT(m_pResVariable);
    if (getVarType() == VAR_INT) {
        m_intValue = value;
        return true;
    }
    return false;
}

bool Variable::setValue(float value) {
#line 70
    MM_ASSERT(m_pResVariable);
    if (getVarType() == VAR_FLOAT) {
        m_floatValue = value;
        return true;
    }
    return false;
}

bool Variable::getValue(int* pValue) const {
#line 88
    MM_ASSERT(m_pResVariable);
    if (getVarType() == VAR_INT) {
        *pValue = m_intValue;
        return true;
    }
    return false;
}

bool Variable::getValue(float* pValue) const {
#line 106
    MM_ASSERT(m_pResVariable);
    if (getVarType() == VAR_FLOAT) {
        *pValue = m_floatValue;
        return true;
    }
    return false;
}

const char* Variable::getName() const {
    return m_pResVariable != nullptr ? m_pResVariable->m_name : "";
}

Variable* findVariable(mm::mtl::Vector<Variable>& variables, const char* name) {
    if (variables.size() == 0) {
        return nullptr;
    }
    Variable* it = std::lower_bound(variables.begin(), variables.end(), name,
                                    [](const Variable& variable, const char* key) {
                                        return strcmp(variable.getName(), key) < 0;
                                    });
    if (it != variables.end() && strcmp(it->getName(), name) == 0) {
        return it;
    }
    return nullptr;
}

const Variable* findVariable(const mm::mtl::Vector<Variable>& variables, const char* name) {
    if (variables.size() == 0) {
        return nullptr;
    }
    const Variable* it = std::lower_bound(variables.begin(), variables.end(), name,
                                          [](const Variable& variable, const char* key) {
                                              return strcmp(variable.getName(), key) < 0;
                                          });
    if (it != variables.end() && strcmp(it->getName(), name) == 0) {
        return it;
    }
    return nullptr;
}

}  // namespace anm

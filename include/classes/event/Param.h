#ifndef CLASSES_EVENT_PARAM_H
#define CLASSES_EVENT_PARAM_H

#include "classes/event/ParamVariable.h"

namespace event {
// table 0x7100B3C038
class Param {
public:
    Param();
    virtual ~Param() {}  // slot 0
    // the i-th value (1.0.0's symbols name it; 3.0.1 leaves it fn_71000B868C)
    ParamVariable& val(unsigned int i);
    // 1.0.0 has it out of line (0x71000975E0); 3.0.1 inlines it
    const ParamVariable& val(unsigned int i) const { return m_vals[i]; }
    // every value's text, each followed by a space
    void createString(mm::mtl::FixStr<256>& str);
    ParamVariable m_vals[10];  // val(i) gives one
};
}  // namespace event

#endif

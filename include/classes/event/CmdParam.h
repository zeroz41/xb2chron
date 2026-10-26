#ifndef CLASSES_EVENT_CMDPARAM_H
#define CLASSES_EVENT_CMDPARAM_H

#include "classes/event/CmdVariable.h"

namespace event {
// table 0x7100B3BF50
class CmdParam {
public:
    virtual ~CmdParam() {}  // slot 0
    // the i-th value (1.0.0 0x7100093778 / const 0x7100093788; 3.0.1 inlines it)
    CmdVariable& val(unsigned long i) { return m_vals[i]; }
    const CmdVariable& val(unsigned long i) const { return m_vals[i]; }
    CmdVariable m_vals[11];  // 0x8 (the name is not the original's)
};
}  // namespace event

#endif

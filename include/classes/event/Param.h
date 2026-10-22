#ifndef CLASSES_EVENT_PARAM_H
#define CLASSES_EVENT_PARAM_H

#include "classes/event/ParamVariable.h"

namespace event {
// table 0x7100B3C038
class Param {
public:
    Param();
    virtual ~Param() {}  // slot 0
    ParamVariable m_vals[10];  // val(i) gives one
};
}  // namespace event

#endif

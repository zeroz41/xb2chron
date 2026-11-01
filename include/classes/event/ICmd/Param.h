#ifndef CLASSES_EVENT_ICMD_PARAM_H
#define CLASSES_EVENT_ICMD_PARAM_H

#include "classes/event/ICmd.h"
#include "classes/event/CmdParam.h"

namespace event {
// table 0x7100B3FCC8
class ICmd::Param {
public:
    virtual ~Param() {}  // slot 0
    // CmdQueue::update builds one from an item's parameters and frame count for each command update
    Param(const CmdParam& param, int frame) : m_param(param), m_frame(frame) {}
    CmdParam m_param;  // 0x8: the values the command was pushed with (the name is not the original's)
    int m_frame;  // 0x118: frames the command has run; updates do their setup at <= 0 (the name is not the original's)
};
}  // namespace event

#endif

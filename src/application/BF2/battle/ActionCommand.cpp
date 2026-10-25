#include "btl/ActionCommand.h"

#include <string.h>

namespace btl {

ActionCommand::ActionCommand() {
    m_type = 0;
    m_actionIDs = 0;
    pad_10_31 = 0;
    pad_0[0] = 0;
    pad_0[1] = 0;
    pad_8[0] = 0;
    pad_8[1] = 0;
}

void ActionCommand::Reset() {
    m_type = 0;
    m_actionIDs = 0;
    pad_10_31 = 0;
    pad_0[0] = 0;
    pad_0[1] = 0;
    pad_8[0] = 0;
    pad_8[1] = 0;
}

bool ActionCommand::IsProcAction(int id) const {
    return (m_actionIDs & (1 << id)) != 0;
}

}  // namespace btl

#include "classes/gf/TUnk_B535D0.h"

namespace gf {

bool TUnk_B535D0::RuleTable::fn_7100290CE0(unsigned int id) {
    if (id == 0) {
        return false;
    }
    return m_rows[id].m_rules[0].m_flag8 & 1;
}

}  // namespace gf

#include "classes/gf/GfGameArena.h"

namespace gf {

bool GfGameArena::RuleTable::fn_7100290CE0(unsigned int id) {
    if (id == 0) {
        return false;
    }
    return m_rows[id].m_rules[0].m_flag8 & 1;
}

}  // namespace gf

#include "gf/GfArenaUtil.h"

namespace gf {

bool GfArenaUtil::isPlayEvent(const mm::mtl::FixedArray<ChBtlInfo, 48>& infos, unsigned int id) {
    if (id == 0) {
        return false;
    }
    return infos[id].m_rules[0].m_flag8 & 1;
}

}  // namespace gf

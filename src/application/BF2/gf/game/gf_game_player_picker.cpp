#include "classes/gf/GfGamePlayerPicker.h"

namespace gf {

bool GfGamePlayerPicker::isPick() {
    GfGamePlayerPicker* picker = get();
    if (picker != nullptr) {
        return picker->m_pick != 0;
    }
    return false;
}

}  // namespace gf

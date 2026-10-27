#include "classes/gf/TUnk_B535D0.h"
#include "classes/gf/TUnk_B52C38.h"
#include "classes/gf/TUnk_B53118.h"
#include "classes/gf/TUnk_B53370.h"
#include "gf/MapjumpCallbackInfo.h"

namespace gf {

void TUnk_B53118::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const&) {
    if (gev == 4) {
        if (TUnk_B535D0* arena = mm::mtl::PtrSingleton<TUnk_B535D0>::sys()) {
            arena->m_msgObj->fn_710028D584();
        }
    }
}

void TUnk_B53370::gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) {}

void TUnk_B53370::gevPlayEvent(gf::GEV gev, unsigned int) {
    switch (static_cast<int>(gev)) {
    case 0xC: m_playState = 1; break;
    case 0xD: m_playState = 3; break;
    case 0xE: m_playState = 2; break;
    default: break;
    }
}

}  // namespace gf

#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/WindManager.h"
#include "classes/fw/WindProbe.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/wnd/WindProbe.h"

namespace fw {

// the constructor (0x71001ABA2C) is not matched yet

WindProbe::~WindProbe() {
    if (WindManager* manager = mm::mtl::PtrSingleton<WindManager>::sys()) {
        manager->removeProbe(this);
    }
    if (m_pProbe != nullptr) {
        m_pProbe->release();
        m_pProbe = nullptr;
    }
}

// update (0x71001ABDB0) is not matched yet

}  // namespace fw

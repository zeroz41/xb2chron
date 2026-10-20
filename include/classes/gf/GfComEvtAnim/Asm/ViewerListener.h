#ifndef CLASSES_GF_GFCOMEVTANIM_ASM_VIEWERLISTENER_H
#define CLASSES_GF_GFCOMEVTANIM_ASM_VIEWERLISTENER_H

#include "classes/gf/GfComEvtAnim/Asm.h"

namespace gf {
// table 0x7100B655F8
class GfComEvtAnim::Asm::ViewerListener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace gf

#endif

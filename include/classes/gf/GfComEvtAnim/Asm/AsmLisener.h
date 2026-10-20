#ifndef CLASSES_GF_GFCOMEVTANIM_ASM_ASMLISENER_H
#define CLASSES_GF_GFCOMEVTANIM_ASM_ASMLISENER_H

#include "classes/gf/GfComEvtAnim/Asm.h"

namespace anm { class AsmAnnotetion; }
namespace anm { namespace AsmListener { class CallBackType; }}

namespace gf {
// table 0x7100B655E0
class GfComEvtAnim::Asm::AsmLisener {
public:
    virtual void callback(anm::AsmListener::CallBackType, anm::AsmAnnotetion const&);  // slot 0
};
}  // namespace gf

#endif

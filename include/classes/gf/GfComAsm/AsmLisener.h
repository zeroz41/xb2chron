#ifndef CLASSES_GF_GFCOMASM_ASMLISENER_H
#define CLASSES_GF_GFCOMASM_ASMLISENER_H

#include "classes/gf/GfComAsm.h"

namespace anm { class AsmAnnotetion; }
namespace anm { namespace AsmListener { class CallBackType; }}

namespace gf {
// table 0x7100B65578
class GfComAsm::AsmLisener {
public:
    virtual void callback(anm::AsmListener::CallBackType, anm::AsmAnnotetion const&);  // slot 0
};
}  // namespace gf

#endif

#ifndef CLASSES_MINIGAME_TORA_MINIGAME_H
#define CLASSES_MINIGAME_TORA_MINIGAME_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace minigame { namespace tora { class minigame; }}

namespace minigame { namespace tora {
// table 0x7100B72080
class minigame : public ::mm::mtl::PtrSingleton< ::minigame::tora::minigame> {
public:
    virtual ~minigame();  // slot 0
};
}}  // namespace minigame::tora

#endif

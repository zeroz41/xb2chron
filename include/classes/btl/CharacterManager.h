#ifndef CLASSES_BTL_CHARACTERMANAGER_H
#define CLASSES_BTL_CHARACTERMANAGER_H

#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class CharacterManager; }

namespace btl {
// table 0x7100B3B280
class CharacterManager : public ::mm::mtl::PtrSingleton< ::btl::CharacterManager>, public ::fw::MessageObject {
public:
    virtual ~CharacterManager();  // slot 0
};
}  // namespace btl

#endif

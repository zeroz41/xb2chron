#ifndef CLASSES_BTL_CHARACTERMANAGER_H
#define CLASSES_BTL_CHARACTERMANAGER_H

#include "classes/fw/MessageObject.h"

namespace btl {
// a base of btl::CharacterManager no evidence names yet
class TUnk_B3B280 {
public:
    virtual ~TUnk_B3B280();
};
// table 0x7100B3B280; base at 0x0 unknown (TUnk_B3B280)
class CharacterManager : public TUnk_B3B280, public ::fw::MessageObject {
public:
    virtual ~CharacterManager();  // slot 0
};
}  // namespace btl

#endif

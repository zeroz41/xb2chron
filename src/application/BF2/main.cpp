#include "gf/FileStaticVec3.h"
#include "classes/minigame/tora/minigame.h"
#include "classes/minigame/tora/MinigameUpdatableObject.h"
#include "classes/BootOption.h"

namespace minigame { namespace tora {

}}  // namespace minigame::tora

BootOption::~BootOption() {
    if (pad_9608 != nullptr) {
        pad_9608 = nullptr;
    }
}

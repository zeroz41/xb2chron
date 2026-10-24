#include "gf/FileStaticVec3.h"
#include "classes/minigame/tora/minigame.h"
#include "classes/minigame/tora/MinigameUpdatableObject.h"

namespace minigame {
namespace tora {

minigame::~minigame() {}

mm::mtl::RTTI MinigameUpdatableObject::m_rtti("MinigameUpdatableObject", &::fw::UpdatableObject::m_rtti, nullptr);

}  // namespace tora
}  // namespace minigame

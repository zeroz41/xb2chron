#ifndef GF_GFSETUPPARAM_H
#define GF_GFSETUPPARAM_H

#include "mtl/AllocHandle.h"

namespace ml { class Scn; }

namespace gf {
// the game's setup parameters (GfManager keeps them at 0x18; the managers' constructors take them): only these fields
// are known (the names are not the original's)
class GfSetupParam {
public:
    ml::Scn* m_scn;  // the scene the map parts create their lights in
    unsigned char pad_8[0x10];
    mtl::ALLOC_HANDLE m_hMem;  // the memory GfMemManager::initializeCore makes the game's allocators' memories in
};
}  // namespace gf

#endif

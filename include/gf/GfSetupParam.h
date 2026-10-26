#ifndef GF_GFSETUPPARAM_H
#define GF_GFSETUPPARAM_H

#include "mtl/AllocHandle.h"
#include "ml/MlMem.h"

namespace ml { class Scn; }
namespace ml { class WinView; }
namespace gf { enum EXEC_STATE : int; }

namespace gf {
// the game's setup parameters (GfManager keeps them at 0x18; the managers' constructors take them): only these fields
// are known (the names are not the original's)
class GfSetupParam {
public:
    // tl::TitleApplet::initialize's: the first three zeroed, the product memory, 0 and a game speed of 1 (1.0.0 the same)
    GfSetupParam()
        : m_scn(nullptr), m_view(nullptr), pad_10(0), m_hMem(ml::MlMem::getProductMem()), pad_1c(0), m_gameSpeed(1.0f) {}

    ml::Scn* m_scn;  // the scene the map parts create their lights in
    ml::WinView* m_view;  // 0x08 the framework's view (tl::TitleApplet::initialize sets its back colour; the name is not the original's)
    unsigned long pad_10;
    mtl::ALLOC_HANDLE m_hMem;  // the memory GfMemManager::initializeCore makes the game's allocators' memories in
    unsigned int pad_1c;
    // GfGameSpeed::build hands it to setGlobalSpeed (the name is not the original's)
    float m_gameSpeed;
    EXEC_STATE m_execState;  // GfManager::build passes it to setExec
    // GfStaticRes::initialize loads "/camera/params_dlc.gca" for "/camera/params.gca" when it is set
    bool m_dlcCameraParam;
    unsigned char pad_29[0x7];
};
}  // namespace gf

#endif

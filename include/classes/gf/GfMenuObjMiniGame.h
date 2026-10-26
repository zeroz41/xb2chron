#ifndef CLASSES_GF_GFMENUOBJMINIGAME_H
#define CLASSES_GF_GFMENUOBJMINIGAME_H

#include "classes/gf/GfMenuObject.h"

namespace minigame { namespace tora { class MinigameUpdatableObject; }}

namespace gf {
// table 0x7100B636F0
class GfMenuObjMiniGame : public ::gf::GfMenuObject {
public:
    GfMenuObjMiniGame(unsigned int handle);
    virtual ~GfMenuObjMiniGame();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // what initialize creates on "SCR_minigame"; update closes the menu's full-screen layer once it terminates
    minigame::tora::MinigameUpdatableObject* m_minigame;
};
}  // namespace gf

#endif

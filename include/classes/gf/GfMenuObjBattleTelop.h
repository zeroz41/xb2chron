#ifndef CLASSES_GF_GFMENUOBJBATTLETELOP_H
#define CLASSES_GF_GFMENUOBJBATTLETELOP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B5FD10
class GfMenuObjBattleTelop : public ::gf::GfMenuObject {
public:
    class MainListener;
    class UniteComboListener;
    virtual ~GfMenuObjBattleTelop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // the rest of the layout (the constructor's: a GfMenuSequence at 0x28, three GfMenuReferenceNumber pointers at
    // 0x2C0) is not written yet. The name is not the original's
    unsigned int m_telop;  // 0x24: the open telop's layout (MainListener's 0x21 searches it by s_telopLayouts)
};
}  // namespace gf

#endif

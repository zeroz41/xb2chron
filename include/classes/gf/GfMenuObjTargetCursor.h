#ifndef CLASSES_GF_GFMENUOBJTARGETCURSOR_H
#define CLASSES_GF_GFMENUOBJTARGETCURSOR_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfMenuPosAdapter; }

namespace gf {
// table 0x7100B64B68
// the enemy target cursor (LAY_en_cursor: IMG_en_cursor and its battle variant IMG_en_cursor_btl). The names of the
// fields are not the original's.
class GfMenuObjTargetCursor : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjTargetCursor(unsigned int handle);
    virtual ~GfMenuObjTargetCursor();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void disp(bool disp);  // shows or hides the cursor (external call 0x12)
    // the sequence steps: each returns true when done; m_stepStarted is set while its animation plays
    bool seqEnCursorOpen();
    bool seqEnCursorLock();
    bool seqCursorClose();
    bool seqEnCursorOutScreen();
    bool seqEnCursorInScreen();
    bool seqEnCursorInTarget();
    bool seqEnCursorInBattle();
    void refreshDisp(unsigned int type);  // shows the field (0) or the battle (1) cursor images
    void startCursorAnimation(const char* anim);  // on the cursor and arrow of m_dispType

    unsigned int m_cursor;  // LAY_main, which initialize gives its listener
    // the object it shows the cursor at: GfMenuManager::getTargetObjHandle's when update last saw it change
    GF_OBJ_HANDLE* m_target;
    unsigned int m_cameraType;  // GfMenuManager::getCurCameraType's when update last sent it (event 0x102)
    GfMenuPosAdapter* m_posAdapter;  // keeps LAY_en_cursor at m_target
    GfMenuSequence<GfMenuObjTargetCursor, 8> m_seq;      // open, close and move steps
    GfMenuSequence<GfMenuObjTargetCursor, 8> m_lockSeq;  // the lock step event 0x102 queues
    bool m_stepStarted;
    int pad_564;  // the constructor zeroes it; no code here reads it
    bool m_mini;  // the cursor is out of the screen (its mini animations)
    unsigned int m_dispType;  // 0 field, 1 battle (isInBattle of the target)
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJLVUPMAIN_H
#define CLASSES_GF_GFMENUOBJLVUPMAIN_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "gf/SoundHandle.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
}  // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuDriverList;
// table 0x7100B62E38: the driver level-up menu. Field names are not the original's.
class GfMenuObjLvupMain : public ::gf::GfMenuObject {
public:
    class MainListener;
    class MenuListener;
    class SelectListener;
    GfMenuObjLvupMain(unsigned int handle);
    virtual ~GfMenuObjLvupMain();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // the drivers' level-up marks, per row of m_driverObjs (1.0.0's name)
    void refreshLevelUpInfo();
    // m_seq's jobs (1.0.0's names)
    bool seqExecLevelUp();
    bool seqEndLevelUp();
    bool seqClose();
    bool seqClose2();
    bool seqClose3();
    // 2.0.0's symbols name it. What it does: waits (false) while GfMenuManager::isFading, then true.
    bool seqANG_WaitFade();
    // 2.0.0's symbols name it. What it does: once (m_textOpened), resets m_textContext and opens GfMenuObjCommonText
    // text 0x132 (with GfMenuObjUtil::isValidExpansion(3)) or 0x103 on it; false while that context is active, then
    // sends the open event to "LAY_lv_driverset" of "LAY_main" and returns true.
    bool seqANG_Notice();

    ui::UISelectObjList* m_modeList;  // 0x28: "LAY_mode_sltag@%02d" of "LAY_mode_menu"
    GfMenuDriverList* m_drivers;  // 0x30: the party's drivers (setupFromParty, type 0)
    ui::UISelectObjList* m_driverObjs;  // 0x38: "LAY_lv_drinfo@%02d" of "LAY_lv_driverset"
    ui::UICtrlCursorSelect* m_cursor;  // 0x40: "IMG_lv_drcursor" on m_driverObjs
    // 0x48: the mode menu's choice (MenuListener's case 8 stores it; 2 while the driver list has the input)
    int m_mode;
    GfMenuSequence<GfMenuObjLvupMain, 8> m_seq;  // 0x50
    bool m_textOpened;  // 0x2E0: seqANG_Notice has opened its text
    int pad_2E4;  // the constructor clears it
    unsigned char pad_2E8[8];
    GfMenuCallContext* m_textContext;  // 0x2F0: GfMenuObjCommonText's
    GfMenuCallContext* m_selectContext;  // 0x2F8: GfMenuObjLvupSelect's
    bool m_levelUp;  // 0x300: the level select's result asks for the level-up effect
    SoundHandle m_jingle;  // 0x304: seqClose2's jingle, seqClose3 waits for it
};
}  // namespace gf

#endif

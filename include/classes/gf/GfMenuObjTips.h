#ifndef CLASSES_GF_TUNK_B64C98_H
#define CLASSES_GF_TUNK_B64C98_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "classes/ui/UIObjectListener.h"

namespace gf { class GfMenuCallContext; }
namespace gf { class GfMenuIDList; }

namespace gf {
// table 0x7100B64C98, no RTTI and no 1.0.0 symbol: the menu object of gf_menu_obj_tips.cpp (its file name and its
// BDAT tips table 0x102 suggest a tips menu; the class name is not the original's). Its layout is the battle
// challenge tutorial's (GfMenuObjBtlchTutorial).
class GfMenuObjTips : public ::gf::GfMenuObject {
public:
    GfMenuObjTips(unsigned int handle);
    virtual ~GfMenuObjTips();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name it. What it does: registers full-screen layer 0x12E's open parameter, the menu id its caller
    // (startBtlchTutorial) passes.
    static void registStartTutorialID(unsigned int menuId);
    // 2.0.0's symbols name it. What it does: sends the open event with its argument to "LAY_tutorial" under
    // attached object 0x89 (GfMenuManager::startBtlchTutorial calls it).
    static void start(unsigned int param);
    // 2.0.0's symbols name it (they were free functions in gf before). What it does: for a tips id inside BDAT file
    // 0x102's id range (from Bdat::getIdTop), sets bit 0 of local game flag 2's entry id - top + 0xEF05;
    // ScriptPlayText's ui unlockTips passes its script argument.
    static void unlockTips(unsigned int id);
    // 2.0.0's symbols name it. What it does: for an id at or past BDAT file 0x102's Bdat::getIdTop, clears bit 1 of
    // local game flag 2's entry id - top + 0xEF05 (GfGameFlag::getLocal, then setLocal with value & 0xFFFD).
    // GfMenuManager::gevChangeScenarioFlag passes 0x92 and 0x93 for scenario flag 0x2B38.
    static void setTipsNoView(unsigned int id);
    // 2.0.0's symbols name it. What it does: shows LAY_list's items from
    // BDAT table 0x102 rows of m_idList's page entries, and the cursor on the selected one.
    // Its bool: ListListener passes false at both calls and the body never reads it.
    void refreshList(bool);
    // 2.0.0's symbols name it. What it does: for a tips id at or past BDAT table 0x102's id top, a row whose "page" is
    // 0 answers m_onlyIra, any other row bit 0 of local game flag 2's entry id - top + 0xEF05.
    bool isUnlockTipsID(unsigned int id);
    // 2.0.0's symbols name it. What it does: when isUnlockTipsID(id) answers true, sets bit 1 of local game flag 2's
    // entry id - top + 0xEF05 (BDAT table 0x102's id top).
    void setViewTipsID(unsigned int id);

    class ListListener;
    class TutorialListener;

    GfMenuSequence<GfMenuObjTips, 2> m_seq;      // 0x28 (the name is not the original's)
    GfMenuSequence<GfMenuObjTips, 8> m_mainSeq;  // 0xF0 (the name is not the original's)
    GfMenuCallContext* m_context;  // 0x380: the constructor's create, the destructor releases it
    void* m_reserved;  // 0x388: cleared by the constructor, never read in this unit (the name is not the original's)
    GfMenuIDList* m_idList;  // 0x390: the constructor's create, the destructor releases it
    bool m_fromLayer;  // 0x398: initialize got a full-screen layer parameter (the name is not the original's)
    // 0x399: initialize sets it from GfMenuManager::isOnlyIra when cleared-game tips show; isUnlockTipsID answers it
    // for page-0 rows (the name is not the original's)
    bool m_onlyIra;

    // 2.0.0's symbols name it (lbl_7100EAB930). True while an instance lives.
    static bool s_Open;
};

// table 0x7100B64CE0: LAY_list's listener (initialize news it; the symbols name the table)
class GfMenuObjTips::ListListener : public ::ui::UIObjectListener {
public:
    ListListener(GfMenuObjTips* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    GfMenuObjTips* m_owner;
};

// table 0x7100B64D08: LAY_tutorial's listener (initialize news it; the symbols name the table)
class GfMenuObjTips::TutorialListener : public ::ui::UIObjectListener {
public:
    TutorialListener(GfMenuObjTips* owner) : m_textCount(0), m_tipsId(0), m_textIndex(0), m_bgType(0), m_owner(owner) {}
    virtual ~TutorialListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // the field names are not the original's
    int m_textCount;        // 0xC: reciveEvent's open (1): the "LAY_text@%02d" children
    unsigned int m_tipsId;  // 0x10: the tips row shown (0x21's id); a close (8) sends it to LAY_list
    int m_textIndex;        // 0x14: the index of the shown text with the greatest window_y
    int m_bgType;           // 0x18: the row's "bg_type" whose "LAY_bg@%02d" is faded in (0: none)
    GfMenuObjTips* m_owner;
};
}  // namespace gf

#endif

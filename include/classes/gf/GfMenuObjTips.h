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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit holds only this
    // class's functions. What it does: sends the open event with its argument to "LAY_tutorial" under attached
    // object 0x89 (startBtlchTutorial calls it).
    static void fn_7100487A1C(int param);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit holds only this
    // class's functions and the list listener calls it on its owner. What it does: shows LAY_list's items from
    // BDAT table 0x102 rows of m_idList's page entries, and the cursor on the selected one.
    // Its argument: the list listener passes 0 at both calls and the body never reads it; the calls keep
    // `mov w1, wzr`, so the original handed it to some header inline (dead-argument elimination would drop it
    // otherwise); which one is unknown.
    void fn_71004881B8(int);
    // 2.0.0's symbols name it. What it does: for a tips id at or past BDAT table 0x102's id top, a row whose "page" is
    // 0 answers m_regionJP, any other row bit 0 of local game flag 2's entry id - top + 0xEF05.
    bool isUnlockTipsID(unsigned int id);
    // 2.0.0's symbols name it. What it does: when isUnlockTipsID(id) answers true, sets bit 1 of local game flag 2's
    // entry id - top + 0xEF05 (BDAT table 0x102's id top).
    void setViewTipsID(unsigned int id);

    class TUnk_B64CE0;
    class TUnk_B64D08;

    GfMenuSequence<GfMenuObjTips, 2> m_seq;      // 0x28 (the name is not the original's)
    GfMenuSequence<GfMenuObjTips, 8> m_mainSeq;  // 0xF0 (the name is not the original's)
    GfMenuCallContext* m_context;  // 0x380: the constructor's create, the destructor releases it
    void* m_reserved;  // 0x388: cleared by the constructor, never read in this unit (the name is not the original's)
    GfMenuIDList* m_idList;  // 0x390: the constructor's create, the destructor releases it
    bool m_fromLayer;  // 0x398: initialize got a full-screen layer parameter (the name is not the original's)
    // 0x399: initialize sets it from GfMenuManager::isRegionJP when cleared-game tips show; isUnlockTipsID answers it
    // for page-0 rows (the name is not the original's)
    bool m_regionJP;

    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB930). True while an instance lives.
    static bool s_exists;
};

// table 0x7100B64CE0: LAY_list's listener (initialize news it)
class GfMenuObjTips::TUnk_B64CE0 : public ::ui::UIObjectListener {
public:
    TUnk_B64CE0(GfMenuObjTips* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B64CE0() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    GfMenuObjTips* m_owner;
};

// table 0x7100B64D08: LAY_tutorial's listener (initialize news it)
class GfMenuObjTips::TUnk_B64D08 : public ::ui::UIObjectListener {
public:
    TUnk_B64D08(GfMenuObjTips* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B64D08() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    GfMenuObjTips* m_owner;
};
}  // namespace gf

#endif

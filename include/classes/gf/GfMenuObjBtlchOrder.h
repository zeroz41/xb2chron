#ifndef CLASSES_GF_TUNK_B606F0_H
#define CLASSES_GF_TUNK_B606F0_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "classes/ui/UIObjectListener.h"

namespace gf { class GfMenuIDList; }
namespace gf { class GfMenuDriverList; }
namespace gf { class GfMenuBladeList; }
namespace gf { class GfMenuCallContext; }
namespace gf { class GAME_VOICE_HANDLE; }
namespace ui { class UICtrlCursorSelect; }

namespace gf {
// table 0x7100B606F0, no RTTI and no 1.0.0 symbol: the menu object of gf_menu_obj_btlch_order.cpp (its file name, its
// list of battle challenges with their rules, records and difficulty suggest a battle challenge order/selection
// menu; the class name is not the original's)
class GfMenuObjBtlchOrder : public ::gf::GfMenuObject {
public:
    GfMenuObjBtlchOrder(unsigned int handle);
    virtual ~GfMenuObjBtlchOrder();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name it. What it does: shows the selected difficulty (m_difficulty): "TXT_difficulty_index" gets
    // BDAT 0x169's message for it, "IMG_list_base"/"IMG_difficulty_base" its animation, "IMG_list_item_base@01" its
    // colour, and GfMenuReference::fn_71003692E4 gets the option value (initialize and the list listener call it).
    void refreshDifficulty();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit holds only this
    // class's functions. What it does: refreshes the selected challenge's detail panes (initialize and the list
    // listener call it).
    void fn_71003AE994();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit holds only this
    // class's functions; fn_71003AE994 calls it.
    void fn_71003AF4C8(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member because its unit holds only
    // this class's functions and it takes no instance; the list listener calls it.
    static bool fn_71003AF654(unsigned int id);
    // 2.0.0's symbols name them. What they do: seqWaitVoice waits for m_voice to end (stopping it when
    // GfMenuObjUtil::isVoiceSkip holds) and clears it; seqClose terminates the menu's layer; seqWaitTutorial waits
    // until GfMenuManager::isOpenBtlchTutorial no longer holds; seqReturn fades LAY_main's LAY_header, LAY_list and
    // LAY_detail in.
    bool seqWaitVoice();
    bool seqClose();
    bool seqWaitTutorial();
    bool seqReturn();

    class ListListener;
    class LimitListener;

    GfMenuIDList* m_idList;  // 0x28: the constructor's create, the destructor releases it
    GfMenuDriverList* m_driverList;  // 0x30: the constructor's create, the destructor releases it
    ui::UICtrlCursorSelect* m_cursor;  // 0x38: initialize's createCursor, the destructor releases it
    GfMenuCallContext* m_context;  // 0x40: the constructor's create, the destructor releases it
    unsigned int pad_48;
    unsigned int m_difficulty;  // 0x4C: GfMenuObjOption's index of the option's value (the name is not the original's)
    unsigned int m_difficultyCount;  // 0x50: GfMenuObjOption::getDifficultyMax (the name is not the original's)
    unsigned char pad_54[0x4];
    GfMenuDriverList* m_limitDrivers;  // 0x58: LAY_limit's drivers (the name is not the original's)
    GfMenuBladeList* m_limitBlades;  // 0x60: LAY_limit's blades (the name is not the original's)
    GAME_VOICE_HANDLE* m_voice;  // 0x68: initialize's playVoice (the name is not the original's)
    GfMenuSequence<GfMenuObjBtlchOrder, 4> m_seq;  // 0x70 (the name is not the original's)
};

// table 0x7100B60758: LAY_list's listener (initialize news it)
class GfMenuObjBtlchOrder::ListListener : public ::ui::UIObjectListener {
public:
    ListListener(GfMenuObjBtlchOrder* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    GfMenuObjBtlchOrder* m_owner;
};

// table 0x7100B60780: LAY_limit's listener (initialize news it)
class GfMenuObjBtlchOrder::LimitListener : public ::ui::UIObjectListener {
public:
    LimitListener(GfMenuObjBtlchOrder* owner) : pad_0C(), m_owner(owner) {}
    virtual ~LimitListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    GfMenuObjBtlchOrder* m_owner;
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_TUNK_B60848_H
#define CLASSES_GF_TUNK_B60848_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "classes/gf/TUnk_B607D8.h"
#include "classes/ui/UIObjectListener.h"

namespace gf { class GfMenuCallContext; }
namespace gf { class GfMenuIDList; }

namespace gf {
// table 0x7100B60848, no RTTI and no 1.0.0 symbol: the menu object of gf_menu_obj_btlch_tutorial.cpp (its file name
// and its "LAY_tutorial" layout suggest a battle challenge tutorial; the class name is not the original's)
class TUnk_B60848 : public ::gf::GfMenuObject {
public:
    TUnk_B60848(unsigned int handle);
    virtual ~TUnk_B60848();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit holds only this
    // class's functions. What it does: registers full-screen layer 0x67's open parameter, the menu id its caller
    // (fn_710035A388) passes.
    static void fn_71003B2A90(unsigned int menuId);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit holds only this
    // class's functions. What it does: sends the open event with its argument to "LAY_tutorial" under attached
    // object 0x89 (fn_710035A388 calls it).
    static void fn_71003B2ABC(int param);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit holds only this
    // class's functions. What it does: returns s_exists (set while an instance lives).
    static bool fn_71003B2B30();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit holds only this
    // class's functions. What it does: returns true once the UI manager is not loading (a sequence job's shape).
    bool fn_71003B3ECC();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit holds only this
    // class's functions and the list listener calls it on its owner. What it does: shows LAY_list's items, each the
    // "title" text of BDAT table 0x101 row of m_idList's page entry, and the cursor on the selected one.
    void fn_71003B2F98();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they are m_mainSeq's
    // jobs. What they do: fn_71003B3EF4 resets m_context, starts it with m_telopParam (TUnk_B607D8::fn_71003B0CE4)
    // and queues fn_71003B3F7C; fn_71003B3F7C waits for the context to end, then queues a 4-frame wait and
    // fn_71003B3EF4 again.
    bool fn_71003B3EF4();
    bool fn_71003B3F7C();

    class TUnk_B60890;
    class TUnk_B608B8;

    GfMenuSequence<TUnk_B60848, 2> m_seq;      // 0x28 (the name is not the original's)
    GfMenuSequence<TUnk_B60848, 8> m_mainSeq;  // 0xF0 (the name is not the original's)
    GfMenuCallContext* m_context;  // 0x380: the constructor's create, the destructor releases it
    TUnk_B607D8::OpenParam m_telopParam;  // 0x388: what fn_71003B3EF4 opens the telop with (the name is not the original's)
    GfMenuIDList* m_idList;  // 0x390: the constructor's create, the destructor releases it
    bool m_fromLayer;  // 0x398: initialize got a full-screen layer parameter (the name is not the original's)

    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAA1C8). True while an instance lives.
    static bool s_exists;
};

// table 0x7100B60890: LAY_list's listener (initialize news it)
class TUnk_B60848::TUnk_B60890 : public ::ui::UIObjectListener {
public:
    TUnk_B60890(TUnk_B60848* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B60890() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    TUnk_B60848* m_owner;
};

// table 0x7100B608B8: LAY_tutorial's listener (initialize news it)
class TUnk_B60848::TUnk_B608B8 : public ::ui::UIObjectListener {
public:
    TUnk_B608B8(TUnk_B60848* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B608B8() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    TUnk_B60848* m_owner;
};
}  // namespace gf

#endif

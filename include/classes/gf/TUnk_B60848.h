#ifndef CLASSES_GF_TUNK_B60848_H
#define CLASSES_GF_TUNK_B60848_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

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

    GfMenuSequence<TUnk_B60848, 2> m_seq;      // 0x28 (the name is not the original's)
    GfMenuSequence<TUnk_B60848, 8> m_mainSeq;  // 0xF0 (the name is not the original's)
    GfMenuCallContext* m_context;  // 0x380: the constructor's create, the destructor releases it
    unsigned long pad_388;
    GfMenuIDList* m_idList;  // 0x390: the constructor's create, the destructor releases it
    bool pad_398;

    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAA1C8). True while an instance lives.
    static bool s_exists;
};
}  // namespace gf

#endif

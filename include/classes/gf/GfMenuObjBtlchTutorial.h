#ifndef CLASSES_GF_TUNK_B60848_H
#define CLASSES_GF_TUNK_B60848_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "classes/gf/GfMenuObjBtlchTelop.h"
#include "classes/ui/UIObjectListener.h"

namespace gf { class GfMenuCallContext; }
namespace gf { class GfMenuIDList; }

namespace gf {
// table 0x7100B60848, no RTTI and no 1.0.0 symbol: the menu object of gf_menu_obj_btlch_tutorial.cpp (its file name
// and its "LAY_tutorial" layout suggest a battle challenge tutorial; the class name is not the original's)
class GfMenuObjBtlchTutorial : public ::gf::GfMenuObject {
public:
    GfMenuObjBtlchTutorial(unsigned int handle);
    virtual ~GfMenuObjBtlchTutorial();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name it. What it does: registers full-screen layer 0x67's open parameter, the menu id its caller
    // (startBtlchTutorial) passes.
    static void registStartTutorialID(unsigned int menuId);
    // 2.0.0's symbols name it. What it does: sends the open event with its argument to "LAY_tutorial" under
    // attached object 0x89 (GfMenuManager::startBtlchTutorial calls it).
    static void start(unsigned int param);
    // 2.0.0's symbols name it. What it does: returns s_Open (set while an instance lives).
    static bool isOpen();
    // 2.0.0's symbols name it. What it does: returns true once the UI manager is not loading (a sequence job's shape).
    bool seqWaitLoading();
    // 2.0.0's symbols name it. What it does: shows LAY_list's items, each the "title" text of BDAT table 0x101 row of
    // m_idList's page entry, and the cursor on the selected one.
    void refreshList();
    // 2.0.0's symbols name them. What they do: seqStartTelop resets m_context, starts it with m_telopParam
    // (GfMenuObjBtlchTelop::open) and queues seqWaitTelop; seqWaitTelop waits for the context to end, then queues a
    // 4-frame wait and seqStartTelop again.
    bool seqStartTelop();
    bool seqWaitTelop();

    class ListListener;
    class TutorialListener;

    GfMenuSequence<GfMenuObjBtlchTutorial, 2> m_seq;      // 0x28 (the name is not the original's)
    GfMenuSequence<GfMenuObjBtlchTutorial, 8> m_mainSeq;  // 0xF0 (the name is not the original's)
    GfMenuCallContext* m_context;  // 0x380: the constructor's create, the destructor releases it
    GfMenuObjBtlchTelop::OpenParam m_telopParam;  // 0x388: what seqStartTelop opens the telop with (the name is not the original's)
    GfMenuIDList* m_idList;  // 0x390: the constructor's create, the destructor releases it
    bool m_fromLayer;  // 0x398: initialize got a full-screen layer parameter (the name is not the original's)

    // 2.0.0's symbols name it (lbl_7100EAA1C8). True while an instance lives.
    static bool s_Open;
};

// table 0x7100B60890: LAY_list's listener (initialize news it)
class GfMenuObjBtlchTutorial::ListListener : public ::ui::UIObjectListener {
public:
    ListListener(GfMenuObjBtlchTutorial* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    GfMenuObjBtlchTutorial* m_owner;
};

// table 0x7100B608B8: LAY_tutorial's listener (initialize news it)
class GfMenuObjBtlchTutorial::TutorialListener : public ::ui::UIObjectListener {
public:
    TutorialListener(GfMenuObjBtlchTutorial* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TutorialListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    GfMenuObjBtlchTutorial* m_owner;
};
}  // namespace gf

#endif

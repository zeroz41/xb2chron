#ifndef CLASSES_GF_GFMENUOBJQUESTLIST_H
#define CLASSES_GF_GFMENUOBJQUESTLIST_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuReferenceQuest.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/EventData.h"

namespace ui { class UICtrlCursorSelect; class UISelectObjList; class UIObjectAcc; }
namespace gf { class GfMenuCallContext; class GfMenuItemList; class GfMenuQuestList; }

namespace gf {
// table 0x7100B64318
class GfMenuObjQuestList : public ::gf::GfMenuObject {
public:
    class DetailListener;
    class ListListener;
    class MainListener;
    class TabListener;
    class TabOpenListener;
    class TabSelectListener;
    class TaskListener;
    class ThumbListener;
    // what registOpenParam passes to the next open as its layer's first parameter; initialize reads it back as the
    // quest to show (the parent of the one given). The name is not the original's.
    struct OpenParam {
        unsigned int m_questId;
    };
    GfMenuObjQuestList(unsigned int handle);
    virtual ~GfMenuObjQuestList();  // slot 0
    static void registOpenParam(const OpenParam& param);
    virtual void initialize();  // slot 2
    void initializeSub(ui::UIObjectAcc& main);
    void setupList(unsigned int quest);  // selects the parent of that quest when it is listed
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    void changeView(unsigned int view);
    bool changeThumbPage(int page);  // false when there is one page or none
    bool seqActivateStart();
    bool seqActivateSelect();
    bool seqEnd();
    // sends an event of that type to an object, to LAY_main when it is 0 (the listeners pass a sibling they search
    // for, or their own object). Inline: its UIObjectAcc and EventData sit above the callers' locals in their
    // frames. The name is not the original's.
    void sendMenuEvent(unsigned int handle, unsigned short type) {
        if (handle == 0) {
            handle = ui::UIObjectAcc(m_handle, "LAY_main").m_handle;
        }
        ui::EventData event;
        event.m_type = type;
        GfMenuObject::sendEvent(handle, event, 0.0f);
    }

    unsigned char pad_24[4];
    // the field names below are not the original's
    GfMenuQuestList* m_questLists[2];          // created by initialize, released by the destructor
    ui::UICtrlCursorSelect* m_cursors[3];      // created by initializeSub over m_selectLists[0..]
    unsigned char pad_50[8];
    unsigned int m_view;                       // changeView: 0 thumbnails, 1 list; kept in GfMenuFlag 1
    unsigned int m_menuFlag2;                  // kept in GfMenuFlag 2 between opens
    unsigned int m_menuFlag3;                  // kept in GfMenuFlag 3 between opens
    unsigned char pad_64[4];
    ui::UISelectObjList* m_selectLists[5];     // created by initializeSub
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numbers[2];
    // both created by the constructor and released by the destructor; only the first is cleared before (the
    // constructor stores 0 to 0x0A0 but not to 0x0A8). seqActivateSelect pops m_context's result.
    GfMenuCallContext* m_context;
    GfMenuCallContext* m_subContext;
    GfMenuSequence<GfMenuObjQuestList, 8> m_seq;  // run by update
    unsigned int m_quest;                      // seqActivateSelect makes it the current quest
    unsigned int m_closeHandle;                // seqEnd sends 0x103 to it (LAY_main's when 0) and clears it
    mm::mtl::IntrusivePtr<GfMenuReferenceQuest> m_references[2];
    GfMenuItemList* m_itemList;                // TaskListener fills it; released by the destructor
    // set by the constructor, cleared by MainListener on 0x24; while set, MainListener closes (2, 0x22) with a fade
    // preset instead of requesting event 3 at once (the name is not the original's)
    bool m_closeWithFade;
    unsigned int m_openQuest;                  // initialize: the open parameter's quest (its parent if any)
    bool m_hasOpenQuest;                       // initialize: an open parameter was registered
};
}  // namespace gf

#endif

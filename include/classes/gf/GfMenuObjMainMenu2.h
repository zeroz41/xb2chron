#ifndef CLASSES_GF_GFMENUOBJMAINMENU2_H
#define CLASSES_GF_GFMENUOBJMAINMENU2_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "mm/mtl/FixedVector.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf { class GfMenuBladeList; class GfMenuCallContext; class GfMenuDriverList; class SelectionChecker; }
namespace mm { namespace mtl { class ReferenceObject; } }
namespace ui { class UICtrlCursorSelect; class UIObjectAcc; }

namespace gf {
// table 0x7100B62FB8
class GfMenuObjMainMenu2 : public ::gf::GfMenuObject {
public:
    class ChrChangeListener;
    class CloseListener;
    class ContentsListener;
    class IndexListener;
    class MainListener;
    // what registOpenParam keeps for the next open: GfMenuManager::setMainmenuOpenMap passes 1,
    // setMainmenuOpenSystem 6 (5 in 3.0.1 when GfMenuObjUtil::isValidExpansion(3) answers true)
    // (the field name is not the original's)
    struct OpenParam {
        unsigned int m_page;
    };
    static void registOpenParam(const OpenParam& param);
    // what the character change listeners (this class's and GfMenuObjBlWeapon2's) hand the *ChrChangeSub helpers
    // (0x38 bytes on their stacks). The field names are not the original's.
    struct ChrChangeParam {
        ChrChangeParam()
            : m_listKind(0), pad_04(false), m_prevKind(0), m_isOpen(false), m_target(0), m_driverList(nullptr),
              m_bladeList(nullptr), m_driverId(0), pad_2C(true), m_subHandle(0) {}
        int m_listKind;  // 0x0 the list shown: 0 the drivers, 1 and 2 the blades
        bool pad_04;  // MainMenu2's open (0x21) sets it when the event's third parameter is 1
        int m_prevKind;  // 0x8 the listener's list kind before this event
        bool m_isOpen;  // 0xC the listener's state was 1 (open)
        unsigned int m_target;  // 0x10 BlWeapon2: the open event's object / LAY_chips; MainMenu2: its own 0x88
        GfMenuDriverList* m_driverList;  // 0x18
        GfMenuBladeList* m_bladeList;  // 0x20
        unsigned int m_driverId;  // 0x28 MainMenu2's open: GfMenuReference::getReferenceDriverID(0)
        bool pad_2C;  // MainMenu2's open clears it for list kind 3
        unsigned int m_subHandle;  // 0x30 the handle openChrChangeSub returned last time
    };
    // what the character change listeners (this class's and GfMenuObjBlWeapon2's) keep between events, 0xC-0x1B of
    // each (their constructors zero it). Inferred, not the original's: a 4-aligned block, since their reads of
    // m_listKind and m_subHandle stay two 4-byte loads (fields of the listener itself at 0x10 would be widened).
    struct ChrChangeState {
        int m_state;  // 1 while the character change is open
        int m_listKind;  // its ChrChangeParam::m_listKind (-1 after the init event)
        unsigned int m_subHandle;  // the handle openChrChangeSub returned
        unsigned int pad_0C;
    };
    static void initChrChangeDr(ui::UIObjectAcc& acc, GfMenuDriverList* list);
    static void initChrChangeBl(ui::UIObjectAcc& acc, GfMenuBladeList* list);
    // true when it opened; the handle it opened goes to the last parameter
    static bool openChrChangeSub(ui::UIObjectAcc& acc, ChrChangeParam& param, unsigned int& handle);
    static void openChrChange2Sub(ui::UIObjectAcc& acc, ChrChangeParam& param);
    static void inputChrChangeSub(ui::UIObjectAcc& acc, ChrChangeParam& param, int index);
    static void closeChrChangeSub(ui::UIObjectAcc& acc, ChrChangeParam& param);
    // 2.0.0's symbols name it. The driver list's counterpart of refreshCharChangeBl: openChrChangeSub and
    // inputChrChangeSub call it with the parameter's driver list.
    static void refreshCharChangeDr(ui::UIObjectAcc& acc, GfMenuDriverList* list);
    static void refreshCharChangeBl(ui::UIObjectAcc& acc, GfMenuBladeList* list);
    GfMenuObjMainMenu2(unsigned int handle);
    virtual ~GfMenuObjMainMenu2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // lays out the main menu's contents entries (their texts, layouts for 7 / 8 entries), its time, money and gift
    // icon. 1.0.0's setupMainMenu took the accessor only; 3.0.1's also reads initialize's m_contentsIds (x1)
    static void setupMainMenu(ui::UIObjectAcc& acc, const mm::mtl::FixedVector<unsigned int, 8>& ids);
    // 1.0.0's helper, inlined in its one caller (the main listener, which is not written yet): moves LAY_move,
    // answers the control it started
    static int moveMainMenu(ui::UIObjectAcc& acc, unsigned int dir, bool);
    // the sequence's term step (a Delegate job; it always answers true)
    bool seqExecTerm();
    // shows or hides the main menu's money, time and clear mark (LAY_info_money, LAY_info_time, LAY_clear_mark)
    static void setDispGold(bool disp);
    static void setCloseKeyEnable(bool enable);
    static void setSystemKeyEnable(bool enable);
    static void closeCharChange();
    // GfMenuObjBlWeapon2::openCharChange passes its LAY_chips handle, 1 and false (the parameter names are not the
    // original's)
    static void openCharChange(unsigned int handle, unsigned int kind, bool flag);
    static void disableCharChange();
    static void cancelEnableMainMenu(bool enable);
    static void setSubIndexText(unsigned int text);
    // a contents entry's sub text (IndexListener's event 0x102 passes TXT_index and TXT_index_shadow, the index and
    // its own object; the parameter names are not the original's)
    static void setContentsSubText(unsigned int handle, unsigned int index, unsigned int owner);
    static bool isOpenCharMenu();
    static void setSubLayer(unsigned int layer);
    static void setGuideText(unsigned int text);
    static void dispGuide(bool disp);
    static void dispCloseButton();
    static void execMapJump();

    // 1.0.0's helper (0x7100485BCC), inlined into its callers in 3.0.1: an event of that type and first parameter
    // to the object of that handle, when there is one. 3.0.1's inlined copies store the type before the parameter
    // (MainListener::reciveEvent's 0x107/0x103 events, dispGuide); 1.0.0's out-of-line copy stored it after
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        if (handle != 0) {
            ui::EventData event;
            event.m_type = type;
            event.m_param0 = param;
            ui::UIManager::sys()->requestObjectEvent(handle, event, 0.0f);
        }
    }

    // 2.0.0's symbols name it. What it does: true when GfMenuObjUtil::isValidExpansion(3) holds and s_bgOpen is set;
    // its one caller is GfMenuObjMainMenu2BG::initialize (0x7100433D04).
    static bool isOpenHitonowaDirect();
    // 2.0.0's symbols name it. What it does: returns s_worldMapOpen; its one caller is GfMenuObjWorldMap::initialize
    // (0x710049626C).
    static bool isOpenDirect();
    // 2.0.0's symbols name it. What it does: s_index while GfMenuObjUtil::isValidExpansion(3) holds, else 0; its one
    // caller is GfMenuObjCharSelectIra::CharListener::reciveEvent.
    static unsigned int getSubIndexTextID();
    // 2.0.0's symbols name it. What it does: on menu layer 3 (GfMenuObjUtil::isValidExpansion(3)) it sets
    // s_closeKeyLocked, disabling the close key first (setCloseKeyEnable(false), inlined) when it locks; its one caller
    // is GfMenuObjPartyForm3's main listener (0x7100453FCC).
    static void lockCloseKey(bool lock);
    // a contents entry's BDAT and text id: the menu table's (0x17F, 0x180 on menu layer 3) title row in 0x117 while
    // its useCond holds, else text 0x67C of 0xF5 (the parameter names are not the original's)
    static void getContentsText(unsigned int index, unsigned char*& bdat, unsigned int& text);
    // 1.0.0's out-of-line helper (0x71004886AC), inlined into setupMainMenu in 3.0.1: the contents entry's text
    // (getContentsText) on the text object of that handle
    static void setContentsText(unsigned int handle, unsigned int index) {
        ui::UIObjectAcc acc(handle);
        unsigned char* bdat;
        unsigned int text;
        getContentsText(index, bdat, text);
        acc.setText(ui::UIStr(bdat, text));
    }

    // the menu the update keeps in s_openMenuID (1.0.0's name); isOpenCharMenu compares it with 0x27 and 0x12D
    static unsigned int s_openMenuID;
    static bool s_cancelEnable;  // 1.0.0's name
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB886). On menu layer 3
    // (GfMenuObjUtil::isValidExpansion(3)) setCloseKeyEnable does nothing while it is set; the close listener
    // clears it, the main listener reads it.
    static bool s_closeKeyLocked;
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB884). initialize clears it, the
    // contents listener sets it, GfMenuObjWorldMap::initialize reads it through isOpenDirect.
    static bool s_worldMapOpen;
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB887). The constructor clears it,
    // the contents listener sets it; isOpenCharMenu answers true while it is set (menu layer 3).
    static bool s_charMenuOpen;
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB888). The constructor and the
    // destructor clear it; GfMenuObjMainMenu2BG::initialize reads it through isOpenHitonowaDirect.
    static unsigned char s_bgOpen;
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB88C). The index listener stores
    // the selected index in it on menu layer 3; getSubIndexTextID returns it.
    static unsigned int s_index;

    unsigned char pad_24[4];
    // the contents' cursor (the main listener shows it and reads its list's selection); released by the destructor
    // (the name is not the original's)
    ui::UICtrlCursorSelect* m_cursor;
    GfMenuCallContext* m_context;  // 0x30 initialize creates it (the name is not the original's)
    unsigned short pad_38;
    // the selected contents entry, an index into m_contentsIds (the main listener reads it; the constructor sets -1;
    // the name is not the original's)
    int m_contentsIndex;
    int pad_40;  // the constructor sets -1
    unsigned int m_menuId;  // 0x44 update copies it to s_openMenuID unless it is 0x28 (the name is not the original's)
    GfMenuDriverList* m_driverList;  // 0x48 (the name is not the original's)
    GfMenuBladeList* m_bladeList;  // 0x50 (the name is not the original's)
    SelectionChecker* m_checker;  // 0x58 (the name is not the original's)
    // 0x60 the contents' BDAT ids initialize collects (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 8> m_contentsIds;
    int pad_88;
    bool pad_8C;
    GfMenuSequence<GfMenuObjMainMenu2, 8> m_seq;  // 0x90 (the name is not the original's)
    bool m_jobStarted;  // 0x320 seqExecTerm reads and clears it (the name is not the original's)
};
}  // namespace gf

#endif

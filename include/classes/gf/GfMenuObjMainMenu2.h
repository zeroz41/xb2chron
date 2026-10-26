#ifndef CLASSES_GF_GFMENUOBJMAINMENU2_H
#define CLASSES_GF_GFMENUOBJMAINMENU2_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "classes/ui/UIManager.h"
#include "mm/mtl/FixedVector.h"
#include "ui/EventData.h"

namespace gf { class GfMenuBladeList; class GfMenuCallContext; class GfMenuDriverList; class SelectionChecker; }
namespace mm { namespace mtl { class ReferenceObject; } }

namespace gf {
// table 0x7100B62FB8
class GfMenuObjMainMenu2 : public ::gf::GfMenuObject {
public:
    class ChrChangeListener;
    class CloseListener;
    class ContentsListener;
    class IndexListener;
    // what registOpenParam keeps for the next open: GfMenuManager::setMainmenuOpenMap passes 1,
    // setMainmenuOpenSystem 6 (5 in 3.0.1 when GfMenuObjUtil::fn_710048FD30(3) answers true)
    // (the field name is not the original's)
    struct OpenParam {
        unsigned int m_page;
    };
    static void registOpenParam(const OpenParam& param);
    GfMenuObjMainMenu2(unsigned int handle);
    virtual ~GfMenuObjMainMenu2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void setCloseKeyEnable(bool enable);
    static void setSystemKeyEnable(bool enable);
    static void closeCharChange();
    static void cancelEnableMainMenu(bool enable);
    static void setSubIndexText(unsigned int text);
    static bool isOpenCharMenu();
    static void setSubLayer(unsigned int layer);
    static void setGuideText(unsigned int text);
    static void dispGuide(bool disp);
    static void dispCloseButton();
    static void execMapJump();

    // 1.0.0's helper (0x7100485BCC), inlined into its callers in 3.0.1: an event of that type and first parameter
    // to the object of that handle, when there is one
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        if (handle != 0) {
            ui::EventData event;
            event.m_param0 = param;
            event.m_type = type;
            ui::UIManager::sys()->requestObjectEvent(handle, event, 0.0f);
        }
    }

    // Placeholder name: new in 3.0.1, nothing in 1.0.0 names it. A static member: it reads this class's statics
    // only. What it does: true when GfMenuObjUtil::fn_710048FD30(3) holds and s_bgOpen is set; its one caller is
    // GfMenuObjMainMenu2BG::initialize (0x7100433D04).
    static bool fn_7100432E2C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0 names it. A static member: it reads this class's statics
    // only. What it does: returns s_worldMapOpen; its one caller is GfMenuObjWorldMap::initialize (0x710049626C).
    static bool fn_7100432E5C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0 names it. A static member: it reads this class's statics
    // only. What it does: s_index while GfMenuObjUtil::fn_710048FD30(3) holds, else 0; its one caller is
    // fn_71003D4B70.
    static unsigned int fn_7100432E6C();

    // the menu the update keeps in s_openMenuID (1.0.0's name); isOpenCharMenu compares it with 0x27 and 0x12D
    static unsigned int s_openMenuID;
    static bool s_cancelEnable;  // 1.0.0's name
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB886). On menu layer 3
    // (GfMenuObjUtil::fn_710048FD30(3)) setCloseKeyEnable does nothing while it is set; the close listener
    // clears it, the main listener reads it.
    static bool s_closeKeyLocked;
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB884). initialize clears it, the
    // contents listener sets it, GfMenuObjWorldMap::initialize reads it through fn_7100432E5C.
    static bool s_worldMapOpen;
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB887). The constructor clears it,
    // the contents listener sets it; isOpenCharMenu answers true while it is set (menu layer 3).
    static bool s_charMenuOpen;
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB888). The constructor and the
    // destructor clear it; GfMenuObjMainMenu2BG::initialize reads it through fn_7100432E2C.
    static unsigned char s_bgOpen;
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB88C). The index listener stores
    // the selected index in it on menu layer 3; fn_7100432E6C returns it.
    static unsigned int s_index;

    unsigned char pad_24[4];
    mm::mtl::ReferenceObject* pad_28;  // released by the destructor
    GfMenuCallContext* m_context;  // 0x30 initialize creates it (the name is not the original's)
    unsigned short pad_38;
    int pad_3C;  // the constructor sets -1
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

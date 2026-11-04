#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GfMenuBladeList; }
namespace gf { class GfMenuDriverList; }
namespace gf { class GfMenuIDList; }
namespace gf { class GfMenuItemList; }
namespace gf { class MenuCommonWindowParam; }
namespace ui { class UICtrlCursorSelect; }
namespace ui { class UIListInfoBase; }
namespace ui { class UISelectObjList; }

namespace gf {
// table 0x7100B61478
class GfMenuObjCommonText : public ::gf::GfMenuObject {
public:
    // what GfPlayFactory::createMenuObjCommonText hands GfSequentialPlay::addMenuObjCommonText
    class OpenKizunaParam;
    class DialogListener;
    class DrChangeListener;
    class ErrorListener;
    class GetItemListener;
    class KizunaListener;
    class MainListener;
    class MerListener;
    class NumSelectListener;
    class OwnerChangeListener;
    class SelectListener;
    class OpenNumSelectParam;
    class OpenSubMenuParam;
    GfMenuObjCommonText(unsigned int handle);
    virtual ~GfMenuObjCommonText();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // opens text `text` for a call context
    static void open(GfMenuCallContext* context, unsigned int text, unsigned int);
    static void open(GfMenuCallContext* context, const MenuCommonWindowParam& param);
    // an item's text (GfMenuManager::openPreciousWindow passes kind 11 and the item id)
    static void openItem(GfMenuCallContext* context, unsigned int kind, unsigned int item);
    static void close();
    // the dialog layout's plugins: both window images fit the text, the cursor follows its base
    static void setupDialog(unsigned int handle);
    // an error text: row `error` of table 0x149 ("name" in table 0x11F), with `value` as the window's pad_44
    static void openError(GfMenuCallContext* context, unsigned int error, unsigned int value);
    // a text of table 0xF6 sent straight to the window (aborts the call context when the row has no text)
    static void openMissionStop(GfMenuCallContext* context, unsigned int text, unsigned int value);
    static void openGetItem(GfMenuCallContext* context, const GfMenuItemList* items);
    // the param is 3.0.1's: the symbol keeps 1.0.0's two-argument spelling
    static void openSubMenu(GfMenuCallContext* context, const GfMenuIDList* ids, const OpenSubMenuParam& param);
    // the items to choose from; `value` goes out as the open event's first word (3.0.1 added it: 1.0.0's
    // openSelectItem takes two arguments)
    static void openSelectItem(GfMenuCallContext* context, const GfMenuItemList* items, unsigned int value);
    // the drivers to change to, `driver` (reference 4) the current one
    static void openDrChange(GfMenuCallContext* context, unsigned int driver, const GfMenuDriverList* drivers);
    // the drivers of references 4 and 5
    static void openOwnerChange(GfMenuCallContext* context, unsigned int driver, unsigned int owner);
    static void openNumSelect(GfMenuCallContext* context, const OpenNumSelectParam& param);
    // the Kizuna dialog for a call context (GfPlayComMenuObjCommonText::start)
    static void openKizunaDialog(GfMenuCallContext* context, const OpenKizunaParam& param);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its address lies in
    // gf_menu_obj_common_text's unit. What it does: GfMenuManager::fn_7100359CD8 calls it in place of
    // open(context, text, 0), passing the reset call context, the window text id (as unsigned int) and its
    // own second argument (gf::GfFieldGrave::create's grave row argument) untouched as an unsigned short.
    static void fn_71003E1F60(GfMenuCallContext* context, unsigned int text, unsigned short arg);
    static GfMenuItemList* s_pItemList;
    static GfMenuIDList* s_pSubMenuIDList;
    static GfMenuDriverList* s_pChangeDrList;
    // set by fn_71003E1F60 once it has opened GfMenuObjNamedDialog's dialog (GfMenuObjNamedDialog::fn_71004451D0); MainListener's close
    // event (0x22) closes that dialog (GfMenuObjNamedDialog::close) and clears it. Proposed name, not the original's:
    // the symbols leave it unnamed (lbl_7100EAA200)
    static bool s_isNamedDialogOpen;

    // the fields from 0x28 (in GfMenuObject's tail padding; the constructor zeroes 0x28..0x8C in one memset): what
    // the constructor, initialize and the listeners store there, released by the destructor. The field names are
    // not the original's.
    ui::UICtrlCursorSelect* m_dialogCursor;  // 0x28: DialogListener's open (GfMenuObjUtil::createCursor)
    ui::UISelectObjList* m_merSelect;        // 0x30: MerListener's open (UISelectObjList::create)
    ui::UICtrlCursorSelect* m_merCursor;     // 0x38: MerListener's open, over m_merSelect
    // 0x40, 0x48: MerListener's numbers (the constructor creates both)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_merNumber1;
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_merNumber2;
    GfMenuBladeList* m_bladeList;    // 0x50: the constructor's; KizunaListener makes its chara adapter from it
    GfMenuDriverList* m_driverList;  // 0x58: the constructor's; KizunaListener makes its chara adapter from it
    ui::UISelectObjList* m_kizunaSelect;  // 0x60: KizunaListener's open (UISelectObjList::create)
    // the driver change list's selection (initialize's UISelectObjList "LAY_dr_change@%02d"), which DrChangeListener's
    // event 6 keeps at s_pChangeDrList's index
    ui::UISelectObjList* m_drChangeListInfo;
    // the selection cursor DrChangeListener hides while the driver change window is open (event 0x21) and shows
    // again when it closes
    ui::UICtrlCursorSelect* m_drChangeCursor;
    // 0x78, 0x80: NumSelectListener's numbers (the constructor creates both)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numSelectNumber1;
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numSelectNumber2;
    // 0x88: NumSelectListener's open stores OpenNumSelectParam::pad_C here; a number's value is a multiple of it
    unsigned int m_numSelectStep;
};
// openKizunaDialog registers the text UIStr(m_bdat, m_id) and sends it with m_value (the field names are not
// the original's)
class GfMenuObjCommonText::OpenKizunaParam {
public:
    unsigned char* m_bdat;  // a message table
    unsigned int m_id;      // the text's id in it
    unsigned int m_value;   // the open event's third word
};
// openNumSelect sends the first three as the open event's first three 16-bit parameters and the last as its third
// word (the field names are not known)
class GfMenuObjCommonText::OpenNumSelectParam {
public:
    unsigned int pad_0;
    unsigned int pad_4;
    unsigned int pad_8;
    unsigned int pad_C;
};
// openSubMenu selects m_index's entry and sends pad_0, pad_4 and pad_6 as the open event's 16-bit parameters
// (GfMenuObjBladeRelease::seqSubMenuOpen fills it; the field names are not the original's)
class GfMenuObjCommonText::OpenSubMenuParam {
public:
    unsigned short pad_0;
    unsigned short m_index;  // the entry selected first (setIndex)
    unsigned char pad_4;
    unsigned short pad_6;
};
}  // namespace gf

#endif

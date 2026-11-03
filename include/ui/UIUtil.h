#ifndef UI_UIUTIL_H
#define UI_UIUTIL_H

#include "fw/LangUtil.h"
#include "classes/fw/MemHandlebaseAllocator.h"
#include "classes/fw/PointerMap.h"

namespace mm { namespace mtl { class IAllocator; } }
namespace mtl { class ALLOC_HANDLE; }

namespace fw { struct PadData; }
namespace ui { class UIObject; }
namespace fw { struct PadData; }
namespace ui { class UICtrlCurve; }
namespace ui { class UILayoutObject; }
namespace mm { template <typename> class Rect; }
namespace mm { namespace mtl { template <int> class FixStr; } }

namespace ui {
// which curve UIUtil::getCurve hands out; the enumerators' names are not the original's, they follow the curve
// classes (1.0.0's names) getCurve returns for each value
enum CURVE_TYPE {
    CURVE_LINEAR,
    CURVE_SIN90,
    CURVE_SIN90_REV,
    CURVE_LINEAR_LOOP,
    CURVE_SIN180,
    CURVE_SIN180_REV,
};
}  // namespace ui

namespace ui { class UIImageObject; }

namespace ui { namespace UIUtil {
extern fw::PointerMap s_ObjPtrMap;                 // the UI objects by handle (registObject)
extern unsigned int s_ObjPtrMax;                   // initObjectMap's count
extern fw::MemHandlebaseAllocator s_ProgAllocator; // getProgAllocator's ("MenuProgram")
extern fw::MemHandlebaseAllocator s_ResAllocator;  // getResourceAllocator's ("MenuResource")
extern unsigned char* s_BdatFPs[17];          // the menu's BDAT tables (initBdatFP), by index
extern unsigned int s_SafeMarginW;                 // setSafeMergin's
extern unsigned int s_SafeMarginH;
// Proposed names, not the original's: the symbols leave them unnamed (lbl_7100B75878, lbl_7100B75880, lbl_7100EC5458)
extern unsigned int s_layerMask;     // the add-on layers usable (fn_7100696950 sets a bit, fn_7100696970 tests one)
extern const char* s_menuDir;        // the menu's root folder ("menu"; fn_7100696930 sets it)
extern unsigned int s_uioReplaceNo;  // MNU_UioReplace's replace column (fn_7100696920 sets it)
void initLayerLib();
void termLayerLib();
void initBdatFP();  // opens the menu's BDAT tables into s_BdatFPs (UIManager::resetData first)
void setupAllocator(mtl::ALLOC_HANDLE handle);  // the menu's program and resource allocators (UIManager's constructor)
void initObjectMap(unsigned int count);
void termObjectMap();
UIImageObject* getImageObject(unsigned int handle);  // null when the handle is no image object's
unsigned int getGroupPriority(unsigned int group);  // a group's priority bits: (group << 5) | 1
void setSafeMergin(unsigned int width, unsigned int height);
unsigned char* getBdatFP(unsigned char index);  // null past the last table
const UICtrlCurve* getCurve(CURVE_TYPE type);  // null for an unknown type
// true when text is a format for count numbers (UIObjectNumberPlugin and UIObjectTimePlugin take the text's own)
bool checkNumberTextFormat(const char* text, unsigned int count);
char getMoneySeparetor(fw::LangType lang);  // the thousands separator of lang's money, 0 for none
mm::mtl::IAllocator* getProgAllocator();
mm::mtl::IAllocator* getResourceAllocator();  // the allocator UI resources are requested from
// the path of a menu motion file (UIMotionLibrary::add requests the resource of its name so)
void makeMenuUIMFileName(mm::mtl::FixStr<128>& path, const char* name);
// the path of a menu UIO file (UIUioLibrary::add requests the resource of its name so)
void makeMenuUIOFileName(mm::mtl::FixStr<128>& path, const char* name);
// the paths of the menu's image, font data, font style and MessageStudio project files (UIFontManager::update requests
// the resources of their names so)
void makeMenuImageFileName(mm::mtl::FixStr<128>& path, const char* name);
void makeMenuFontDataFileName(mm::mtl::FixStr<128>& path, const char* name);
void makeMenuFontStyleFileName(mm::mtl::FixStr<128>& path, const char* name);
void makeMSProjFileName(mm::mtl::FixStr<128>& path, const char* name);
// the paths of a menu layout, particle and environment file (by their symbols)
void makeMenuLayoutFileName(mm::mtl::FixStr<128>& path, const char* name);
void makeMenuUIPFileName(mm::mtl::FixStr<128>& path, const char* name);
void makeMenuEnvFileName(mm::mtl::FixStr<128>& path, const char* name);
UIObject* getObject(unsigned int handle);
// drops a handle: a duplicate's input goes back, its event listener and its handle's map entry go
void releaseObject(unsigned int handle);
unsigned int searchChild(unsigned int handle, const char* name);
void setDispChild(unsigned int handle, bool disp, const char* child);
const fw::PadData* getPadData();  // the UI's pad (the UI manager's input's, else fw::PadManager's control pad)
bool isValid(unsigned int handle);
bool isTerm(unsigned int handle);
UILayoutObject* getLayoutObject(unsigned int handle);  // null when the handle is no layout object's
unsigned long timeSecToUITime(float sec);  // seconds in UI time units
unsigned int getScreenWidth();   // the layer library's screen width
unsigned int getScreenHeight();  // the layer library's screen height
bool adjustScreen(mm::Rect<short>& rect);  // true when it had to move the rectangle onto the screen
// true when it had to move rect into area (UIObjectDockPlugin's execute keeps its object inside its area)
bool adjustRect(mm::Rect<short>& rect, mm::Rect<short>& area);
unsigned int registObject(UIObject* object);  // the handle its object map gives it
// puts the object handle against a side of the object target (0: on its center, 1: left, 2: right, 3: above,
// 4: below), target's rectangle taken by getRect mode 3 when outer, 2 otherwise (the parameter names are not the
// original's)
void setDockPos(unsigned int handle, unsigned int target, unsigned char side, bool outer);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free UIUtil function because its address is
// in ui/UIUtil's unit among UIUtil's functions. What it does: whether bit `bit` of the layer mask lbl_7100B75878 is
// set (1 << bit tested against the word). GfMenuObjUtil::fn_710048FD30 passes its add-on menu layer, and
// ui::UIManager::createLayer/terminateLayer/releaseLayer call it too.
bool fn_7100696970(unsigned int bit);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free UIUtil function because its address is
// in ui/UIUtil's unit among UIUtil's functions. What it does: stores its argument in s_uioReplaceNo, the column
// number makeMenuUIOFileName reads MNU_UioReplace's "replace%02d" from (gf::GfMenuManager's constructor and
// fn_71003597B0 call it).
void fn_7100696920(unsigned int no);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free UIUtil function because its address is
// in ui/UIUtil's unit among UIUtil's functions. What it does: stores the menu's root folder s_menuDir ("menu" until
// set; the makeMenu*FileName paths start with it); gf::GfMenuManager's constructor calls it.
void fn_7100696930(const char* dir);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free UIUtil function because its address is
// in ui/UIUtil's unit next to fn_7100696930. What it does: returns s_menuDir (GfMenuMapInfo::setCurrentMap,
// getMapInfoIndex and GfMenuObjStaffroll::initialize read it).
const char* fn_7100696940();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free UIUtil function because its address is
// in ui/UIUtil's unit next to fn_7100696970. What it does: sets bit `bit` of the layer mask s_layerMask (the bit
// fn_7100696970 tests); gf::GfMenuManager's constructor calls it.
void fn_7100696950(unsigned int bit);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free UIUtil function because its address is
// in ui/UIUtil's unit among UIUtil's functions. What it does: true when `file` is one of the "file" column's values
// of MNU_UioReplace (s_BdatFPs[16]), compared by strcmp; fn_7100353A94 calls it.
bool fn_7100696990(const char* file);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free UIUtil function because its address is
// in ui/UIUtil's unit next to fn_7100696970. What it does: the layer BDAT of an add-on: for 0 the menu's own layer
// table (s_BdatFPs[6], getBdatFP(6)); while bit `dlc` of the layer mask lbl_7100B75878 is set, the table
// "MNU_Layer_Dlc%02d" names (Bdat::getFP); otherwise null. ui::UIManager::createLayer/terminateLayer/releaseLayer
// pass a layer id / 100, GfMenuHUD::initialize calls it too.
unsigned char* fn_7100696A28(unsigned int dlc);
const fw::PadData* getPadData();  // the pad the UI reads this frame (UIManager's, else the control pad's)
unsigned int convUIPadToFWPad(int pad, bool);  // a UI pad button's fw::PadData bits
}}  // namespace ui::UIUtil

#endif

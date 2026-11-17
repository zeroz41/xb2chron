#ifndef GF_GFMENUOBJUTIL_H
#define GF_GFMENUOBJUTIL_H

#include "mm/Col3.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "gf/SoundHandle.h"

namespace gf { class GfMenuCallContext; }
namespace gf { enum PTPOS : unsigned int; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class DataParamAcc; }
namespace gf { class GfMenuBladeList; class SDataGame; }
namespace gf { struct GfRequestBladeData; }
namespace ui { class UIListInfoBase; class UIObjectAcc; }
namespace fw { enum SoundCategory : int; }
namespace fw { enum VibrationID : int; }
namespace gf { class QuestID; }
namespace gf { enum FAVORITE : int; }
namespace ui { class UIStr; class UISelectObjList; }
namespace mm { class Vec3; class Col3; }

namespace gf {
// the menu objects' shared helpers; its functions take no object
class GfMenuObjUtil {
public:
    // the menu's parameters fw::ParamManager holds (getParamMenu; null without them). Only the two times
    // GfMenuFieldSkill reads are known (the names are not the original's).
    struct ParamMenu {
        float m_presetCtrlTime;  // getPresetCtrlTime's for presets 0-5 (the name is not the original's)
        float m_infoWait;   // seconds StateDispInfo waits after a skill
        unsigned char pad_8[0x4];
        // how long GfMenuObjMainMenu2's contents listener moves the main menu background per selection change
        // (the name is not the original's)
        float m_mainMenuBgTime;
        unsigned char pad_10[0x4];
        float m_totalWait;  // seconds StateTotalNext waits
        float m_chainAttackWait;  // GfMenuObjBladeChange::startChainAttack's event delay (the name is not the original's)
    };
    static const ParamMenu* getParamMenu();
    // what startCtrl hands UICtrlManager: the methods to add (m_methods' bits) and how long they run
    struct CtrlParam {
        // its fields the callers' code zeroes; the rest stay as they were
        CtrlParam()
            : m_time(0.0f), m_eventId(0), m_methods(0), m_curve(0), m_reserve(false), m_setDefault(false),
              m_fromDefault(false), m_startFlags(0), m_slot(-1), m_delay(0.0f), m_distance(8), m_scale(0.0f),
              m_rot(0.0f), m_bright(0.0f), m_alpha(0.0f) {}
        float m_time;          // how long the control runs: startCtrl does nothing when it is negative
        // passed on to UICtrlManager::startCtrl with the slot: what the control's end event (3) carries as its first
        // parameter (GfMenuObjMercenaryRoot's open and close controls are 1 and 2)
        int m_eventId;
        unsigned int m_methods;  // bit 0 fades in, bit 1 fades out, bits 3-7 move by m_distance or to m_pos, ...
        int m_curve;           // the methods' ui::CURVE_TYPE
        bool m_reserve;        // what UICtrlManager::reserveCtrlSlot is given when m_slot is -1
        bool m_setDefault;     // UICtrlManager::setDefault on the slot first
        bool m_fromDefault;    // relative to the slot's default transform and display info
        unsigned char pad_13;
        unsigned int m_startFlags;  // how UICtrlManager::startCtrl runs it
        int m_slot;            // the control slot: -1 reserves one
        float m_delay;         // UICtrlManager::setDelayTime
        int m_distance;        // how far the position methods move
        unsigned char pad_24[2];
        ::mm::Pnt<short> m_pos;  // where bit 7's position method moves to (one 4-byte copy: GfMenuObjOCG::seqStartResult)
        float m_scale;         // added to the scale (bit 20's method: to its x only)
        // bit 20's method adds it to the scale's y (the name is not the original's; startCtrl's addScaleMethod)
        float m_scaleY;
        float m_rot;           // added to the rotation
        float m_bright;        // the brightness method's target
        float m_alpha;
        // the colour bit 25's method multiplies by and bit 26's adds (startCtrl's addMulColorMethod /
        // addAddColorMethod; the name is not the original's)
        ::mm::Col3 m_color;
        unsigned char pad_4C[0x4];
        const char* m_motionLib;  // the motion method's library and motion
        const char* m_motion;
    };
    // what startPresetCtrl turns into a CtrlParam: one of its preset fades, in or out
    struct PresetCtrlParam {
        // m_startFlag4 is the callers' (GfMenuObjEnvironmentInfo's and GfMenuObjSpecialGauge's set it). The order
        // of the stores is the original's: GfMenuObjPartyGauge's listener keeps the dead m_slot store (a branch
        // follows), after the m_preset/m_out and flag stores; callers that fade in still set m_preset and m_out
        PresetCtrlParam()
            : m_preset(0), m_out(0), m_slot(-1), m_startFlag1(false), m_startFlag4(false), m_eventId(0), m_delay(0.0f),
              m_child(nullptr) {}
        unsigned int m_preset;  // 0-3 also move the object (CtrlParam methods bits 8-11 in, 12-15 out), 5 scales
        unsigned int m_out;     // 0 fades in, 1 fades out (startPresetCtrl does nothing for others)
        int m_slot;             // CtrlParam::m_slot
        bool m_startFlag1;      // sets CtrlParam::m_startFlags bit 0 (and clears bit 2)
        bool m_startFlag4;      // sets CtrlParam::m_startFlags bit 2
        int m_eventId;          // CtrlParam::m_eventId
        float m_delay;          // CtrlParam::m_delay
        const char* m_child;    // what startCtrl is given for the child
    };
    // what createCursor makes a cursor from: the objects it selects (picked up by name from m_parent's children, or
    // m_names' m_nameCount children) and the cursor object (the names are not the original's)
    struct CursorParam {
        CursorParam() : m_parent(0), m_cursor(0), m_pickup(nullptr), m_names(nullptr), m_nameCount(0), m_type(0) {}
        unsigned int m_parent;
        unsigned int m_cursor;   // UICtrlCursorSelect::create's object
        const char* m_pickup;    // UISelectObjList::pickupObject's name, when not null
        const char** m_names;    // otherwise these children's
        unsigned short m_nameCount;
        unsigned short m_type;   // CursorSetting::setType's
        ui::UICtrlCursorSelect::CursorSetting m_setting;
    };
    static ui::UICtrlCursorSelect* createCursor(CursorParam& param);
    static const char* getMenuMS(unsigned int id);  // a menu message
    static int getFaceIconID(const DataParamAcc& acc);  // an object's face icon, 0 for none
    // a saved game's face icon of a driver (type 3) or blade (type 4), 0 for any other type
    // (GfMenuObjSaveLoad2::refreshSave shows the save's party with it)
    static unsigned int getFaceIconID(const SDataGame& game, unsigned int type, unsigned int id);
    static bool getMenuCondition(unsigned int condition);  // whether a menu's condition is met
    static bool checkCCStart(GfMenuCallContext* context);  // a context that is not running yet
    static bool checkCCNext(GfMenuCallContext* context, unsigned int id);  // a context running on that id
    static void setDockPos(unsigned int handle, unsigned int target, unsigned char pos, bool);
    // like setDockPos, with the target's rect read without its scale (getRect mode 0, or 1 when outer)
    static void setDockPosNoScale(unsigned int handle, unsigned int target, unsigned char side, bool outer);
    static void addPos(unsigned int handle, short x, short y);
    // a blade's or driver's image placement (GfMenuObjBladeRelease::seqOpenImage moves the image by it and scales
    // it); the field names are not the original's
    struct ImageParam {
        short m_x;
        short m_y;
        float m_scale;
    };
    static bool getImageParam(unsigned int type, unsigned int id, ImageParam& param, unsigned int);
    // the slot of the control it starts on the handle (or its child of that name), -1 for none
    static int startCtrl(unsigned int handle, const CtrlParam& param, const char* child);
    // shows count children named by format (from @01) in a column centred on pos, spacing apart (GfMenuObjSalvage's
    // record lays out its LAY_result@%02d rows so)
    static void placeObjectV(unsigned int handle, const char* format, unsigned int count, const mm::Pnt<short>& pos,
                             unsigned int spacing);
    // places the list's objects in a column around center, spacing apart (GfMenuObjTitle::initialize)
    static void placeObjectV(ui::UISelectObjList* list, const mm::Pnt<short>& center, unsigned int spacing);
    // how createFitPlugin's UIObjectFitPlugin fits: its flags and sizes (the names are UIObjectFitPlugin's fields')
    struct FitOption {
        FitOption()
            : m_addHalfSize(false), m_keepScaleX(false), m_keepScaleY(false), m_offsetWidth(0), m_offsetHeight(0),
              m_minWidth(0), m_minHeight(0) {}
        bool m_addHalfSize;
        bool m_keepScaleX;
        bool m_keepScaleY;
        short m_offsetWidth;
        short m_offsetHeight;
        unsigned short m_minWidth;
        unsigned short m_minHeight;
    };
    // a UIObjectFitPlugin on the handle's object over target, with those margins and options
    static void createFitPlugin(unsigned int handle, unsigned int target, int marginWidth, int marginHeight,
                                const FitOption& option);
    static void setChildText(unsigned int handle, const char* child, unsigned short text);  // a registered text
    static void createNumberPlugin(unsigned int handle, int number);
    // the menu objects' UI objects are at their limit: the GfMenuObj*::open functions open nothing then
    static bool isMenuObjectFull();
    static int getCtrlID(unsigned int handle);  // the slot of the control running on the handle, -1 for none
    static void stopCtrl(int slot);  // nothing for -1
    static bool isBusyCtrl(int slot);
    // the length of that motion library's motion (GfMenuObjBlWeapon2::seqSrcLeave times a fade by it)
    static float getCtrlMotionTime(const char* motionLib, const char* motion);
    // the sound of a menu sound table row (BDAT 0x187's resource_id), and its handle (0 when nothing plays)
    static unsigned int playSE(unsigned int se);
    static unsigned int playSE(const char* se);  // a sound by its name
    // places the list's objects in a row around center, width apart (GfMenuObjNpcTelop's listener)
    static void placeObjectH(ui::UISelectObjList* list, const mm::Pnt<short>& center, unsigned int width);
    // places count objects named by format (numbered from 1) in a row around center, width apart (the names are not
    // the original's; GfMenuObjItemList2::initialize places its filter icons, gf_menu_obj_named_list initialize)
    static void placeObjectH(unsigned int handle, const char* format, unsigned int count, const mm::Pnt<short>& center,
                             unsigned int width);
    // count objects named by format (numbered from 1) in a row from left, width apart (GfMenuObjMainMenu2's
    // openChrChange2Sub places its character icons so; the parameter names are not the original's)
    static void placeObjectHLeft(unsigned int handle, const char* format, unsigned int count,
                                 const mm::Pnt<short>& left, unsigned int width);
    // places point along base at ratio (0..1), offset by the short (GfMenuObjEvTheater's sound level bars pass -4;
    // the parameter names are not the original's)
    static void placeObjectHRatio(unsigned int base, unsigned int point, float ratio, short offset);
    static int startPresetCtrl(unsigned int handle, const PresetCtrlParam& param);  // startCtrl's slot
    static bool setPointSpeedRate(ui::UIObjectAcc acc, float rate);  // the pointer's speed over the object
    static short getBtnIconNumber(unsigned int button);  // the icon number of a button
    static short getPadSelectIconNumber(unsigned int select);  // the icon number of a pad selection, 0xFFFF for none
    static unsigned int playBGM(unsigned int bgm, bool, fw::SoundCategory category);  // the handle stopBGM takes
    static void stopBGM(unsigned int handle, float time);
    static bool isValidBlade(unsigned int blade);
    static bool getBladeTeamName(unsigned int blade, ui::UIStr& name);  // false when it has none
    static ui::UIStr getName(const DataParamAcc& acc);
    static void playSECommonFromInput(unsigned int input);  // the common sound for a menu input
    static unsigned int playSECommonCursor();  // the common sound of a cursor move
    static unsigned int playSECommon(unsigned int se);  // one of the common menu sounds (0-2)
    static unsigned int playSECommonDecide();
    static unsigned int playSECommonCancel();
    static void setChildDisp(unsigned int handle, const char* child, bool disp);  // its child of that name
    static void setChildAddColor(unsigned int handle, const char* child, const char* color);  // a named colour
    static void setChildText(unsigned int handle, const char* child, const ui::UIStr& text);
    // shows the child and starts its animation: the child's handle, 0 when there is no such child
    static unsigned int playAnime(unsigned int handle, const char* child, const char* anime);
    static short getPointerSelectIconNumber();  // always 17
    static void suspendCtrl(int slot);  // stops it without its end (nothing for -1)
    static void releaseCtrl(int slot);  // nothing for -1
    static void setCtrlDefault(int slot);  // nothing for -1
    static void setCtrlSpeedFactor(int slot, float factor);  // nothing for -1
    static int getPresetCtrlCurve(unsigned int preset);  // 3.0.1's always 1
    // the time of that preset control (GfMenuObjCharSelect::seqStreamWaitStatDr passes 6)
    static float getPresetCtrlTime(unsigned int preset);
    // sets param up as that preset's fade-in control, with slot as its m_slot (GfMenuObjHitonowa::dispLevel passes
    // 3 and -1)
    static void setPresetCtrl_Fadein(unsigned int preset, CtrlParam& param, int slot);
    // the colour ui::UIColorLibrary names (r, g, b; black without one), in a function-local static
    static const mm::Col3& getPresetColor(const char* name);
    // a world position in view space (out = GfInfo::m_viewMat applied to in)
    static void convViewSpace(mm::Vec3& out, const mm::Vec3& in);
    static unsigned int getLeaderPartyID();  // always 0
    static unsigned int getDriverPartyID(unsigned int driver);  // the driver's party slot, -1 for none
    static bool isExitDriver(unsigned int index);  // a driver in that party slot (index modulo 3)
    // the other common sounds (BDAT 0x187 rows 5, 0xB, 0xC, 0xE)
    static unsigned int playSECommonTab();
    static unsigned int playSECommonSort();
    static unsigned int playSECommonOpenSubMenu();
    static unsigned int playSECommonCloseSubMenu();
    static void stopSE(unsigned int handle, float time);
    static void playVibration(fw::VibrationID id, float scale);
    static bool isQuestCompleted(QuestID id);
    // the current quest of a quest type (GfMenuLocation::refreshLocatorFromQuest passes 0 for its list 0, 1 for list 1)
    static QuestID getCurrentQuest(unsigned int type);
    static void setChildIcon(unsigned int handle, const char* child, unsigned short icon);
    static SoundHandle playJingle(unsigned int jingle);
    // the common fades, in and out: startCtrl's slot (the second argument is the end event's CtrlParam::m_eventId)
    static int setCommonFadeIn(unsigned int handle, unsigned int eventId, unsigned char);
    static int setCommonFadeOut(unsigned int handle, unsigned int eventId, unsigned char);
    // a scroll bar on the handle for the list, its base the child of that name
    static void createVScrollBarPlugin(unsigned int handle, ui::UIListInfoBase* list, const char* base, bool);
    static void setColDefault(unsigned int handle);  // the object's default colours back
    static void setColMulandAdd(unsigned int handle, const char* name);  // the colours of a named preset
    // an elemental combo's attribute and name, from its BDAT row (attribute 0 for an invalid one)
    static unsigned char getElementComboAtr(unsigned int combo);
    static ui::UIStr getElementComboName(unsigned int combo);
    static ui::UIStr getEnemyArtsName(unsigned int arts);
    static bool isEnemyNamed(gf::GF_OBJ_HANDLE* handle);
    static bool isEnemyBoss(gf::GF_OBJ_HANDLE* handle);
    static gf::GF_OBJ_HANDLE* getLeaderBladeHandle(bool);
    static gf::GF_OBJ_HANDLE* getBladeHandleFromPartySlot(unsigned int driver, int slot, bool);
    // the blade id in that slot (back slot) of the party driver's (GfMenuCharDataAdapter::PartyBladeConverter)
    static unsigned int getBladeIDFromPartySlot(unsigned int driver, int slot, bool);
    static unsigned int getBladeIDFromPartyBackSlot(unsigned int driver, int slot, bool);
    // the blade id the driver has in that slot (GfMenuCharDataAdapter::ReferenceBladeSetConverter)
    static unsigned int getBladeIDFromDriverSlot(unsigned int driver, int slot);
    // how many blade slots a driver has: 1, 2 once local flag 0x89FF is 1, 3 once 0x8A00 is 1 (1.0.0's
    // getBladeFromDriver calls getBladeSlotMax at the same place; 1.0.0's body is the same)
    static unsigned int getBladeSlotMax();
    // a combo's effect text, and its effect (3.0.1's always 1) (GfMenuElementComboAdapter's update_*)
    static ui::UIStr getElementComboEffectName(unsigned int combo);
    static unsigned char getElementComboEffect(unsigned int combo);
    // 2.0.0's symbols name it. What it does: whether the add-on menu layer `layer` is usable. False unless bit `layer`
    // of UIStr.cpp's layer mask (lbl_7100B75878; registEnableExpType sets a bit, isEnableExpType tests one,
    // getLayerBdat opens a set layer's "MNU_Layer_Dlc%02d" BDAT) is set; then layer 3 is GfGameManager::isGameTypeIra,
    // layer 2 is always usable, layer 1 is isInstalledBattleArenaContents (add-on content 0x01010003, checked by
    // gf_game_env.cpp's isExistGameAoc), any other layer is not. GfMenuManager's constructor sets bit 1 when
    // isInstalledBattleArenaContents holds, and bit 3 when "menu_ira/font/bf2.wisty" is present (it then gives UIStr
    // the font folder "menu_ira") or add-on content 0x101 is owned. 344 functions call it: 3 at 427 call sites and 1 at
    // 46.
    static bool isValidExpansion(unsigned int layer);
    // 2.0.0's symbols name it. What it does: true when ui::UIUtil::isEnableExpType(1) and
    // GfGameManager::isInstalledBattleArenaContents() hold and GfGameManager::getMapID() is 0x3A. Callers: GfGamePad::
    // eventInGameOpenSkipTravelMenu (refuses the menu then), GfMenuObjMainMenu2::ContentsListener,
    // GfMenuObjMainSubmenu::ListListener, GfMenuObjWorldMap::MapSelectListener and GfMenuObjWorldMap::isEnterMap.
    static bool isInChallengeBattleMap();
    // 2.0.0's symbols name it. What it does: whether blade is one of 1005..1007.
    static bool isBladeHana(unsigned int blade);
    // 2.0.0's symbols name it. What it does: whether blade is one of 1124..1132 (GfMenuCharDataAdapter::update shows a
    // blade object only when this or isValidBlade holds).
    static bool isIraDummyBlade(unsigned int blade);
    // 2.0.0's symbols name it. What it does: false unless GfGameManager::isClearGame; then true when
    // GfDataBlade::isActivateMercenaryTeam holds for blade 1005 or 1006, else whether the game data's short at 0x8E04 is 2.
    static bool isBladeHanaInMercenary();
    // 2.0.0's symbols name it. What it does: true when ui::UIUtil::isEnableExpType(3) and GfGameManager::isGameTypeIra
    // hold and GfGameUtil::isDispSinMask does not; GfMenuCharDataAdapter::update_DR_BtlFace then shows face 0xB for driver 0x14.
    static bool isIraSinMaskOff();
    // 2.0.0's symbols name it. What it does: whether blade is one of 1043..1049
    // (GfMenuObjBlWeapon2::ItemSelectListener::reciveEvent).
    static bool isBladeNoBuildWeapon(unsigned int blade);
    // 2.0.0's symbols name it. What it does: the same body as getBladeSlotMax() (1, 2 once local flag 0x89FF is 1, 3
    // once 0x8A00 is 1; the game data is not read); callers GfMenuObjSaveLoad2::refreshSave and fn_71002EAF78.
    static unsigned int getBladeSlotMax(const SDataGame&);
    // 2.0.0's symbols name it. What it does: 0 unless GfGameManager::isClearGame; then the first of blades 1005, 1006,
    // 1007 that GfDataBlade::isActivateMercenaryTeam holds for, else 0 (GfMenuObjBladeSet2::BladeListListener::reciveEvent).
    static unsigned int getBladeHanaInMercenary();
    // 2.0.0's symbols name it. What it does: false once the game is cleared and driver 4 is
    // GfDataDriver::isActivateUnuse; true when driver 4 is not isActivateParty; else whether more than one of party
    // slots 0-2 has a driver (GfGameParty::getDriverBdatId(slot, 0) != 0) (GfMenuBladeList::setupFromTeam).
    static bool canBladeHanaInMercenary();
    // 2.0.0's symbols name it. What it does: GfDataBlade::setBladeLock(blade, flag), and for blade 1001/1002 the same
    // for both, for 1005..1007 for all three (the blade release, blade set and mercenary form listeners call it).
    static void setBladeFavorite(unsigned int blade, bool flag);
    // 2.0.0's symbols name it. What it does: true when bit 2 of byte 4 of ui::UIUtil::getPadData() is set, else that
    // byte's bit 1 (GfMenuObjFieldSkill::update stops its voice when this and isValidExpansion(3) hold).
    static bool isVoiceSkip();
    // 2.0.0's symbols name it. What it does: spaces the count children of handle named by format (format % 1.., a
    // FixStr) evenly, centred, by the width of the child it names with name (asserts "pszName != 0");
    // gf_menu_obj_btlch_order's LAY_limit listener lays out "LAY_limit_dr@%02d" by "limit_driver" and
    // "LAY_limit_bl@%02d" by "limit_blade" with it.
    static void placeObjectHFromLayout(unsigned int handle, const char* format, unsigned int count, const char* name);
    // the icons of a driver's arts at a level (getArtsIconInfo zeroes it first); the names are not the original's
    struct ArtsIconInfo {
        unsigned int m_type;     // 0xC, 0xD, 0xE for the special kinds
        unsigned int m_enhance;  // the level's enhance effect's icon (4 and up), 0 for none
        unsigned int m_react;    // the reaction's icon, 0 for none
        unsigned int pad_C;
        unsigned int m_range;
    };
    // false for arts 0
    static bool getArtsIconInfo(unsigned int arts, unsigned int level, ArtsIconInfo& info);
    // a message id from a list table (by the list's table and an index)
    static unsigned short getMsgIDFromList(unsigned int list, unsigned short index);
    // (appended by wpntype) the arts the driver can use with the weapon type, and how many (0 for none). 1.0.0's name
    // (getEnableArts(mm::mtl::FixedArray<unsigned int, 4>&, unsigned int, unsigned int)): the symbols call it
    // getEnableArts (1.0.0's GfMenuWeaponTypeAdapter::update_Arts* call getEnableArts at the same sites); 3.0.1
    // added the last two arguments (with add-on menu layer 3 usable, mode 0 with the flag set, or mode 1, also take
    // GfDataDriverArts::getEnableArts's arts of mode 3 or 2); GfMenuWeaponTypeAdapter passes 0 and false
    static unsigned int getEnableArts(mm::mtl::FixedArray<unsigned int, 4>& arts, unsigned int driver,
                                      unsigned int wpnType, PTPOS mode, bool flag);
    // (appended by chardata) used by GfMenuCharDataAdapter::update_*
    static unsigned int convMenuDriverID(unsigned int driver);  // the driver's menu id (0 for none)
    static unsigned int convMenuBladeID(unsigned int blade);    // the blade's menu id
    static unsigned int getDriverClassBuffRatio(unsigned int driverClass, unsigned int index);
    // the level (1-based; 0 for none) of a driver class's buff index (GfMenuCharDataAdapter::update_DR_ClassBuffLv)
    static unsigned int getDriverClassBuffLv(unsigned int driverClass, unsigned int index);
    // the name message (BDAT table 0x127) of a driver class's buff index; 0 for none
    static unsigned int getDriverClassBuffType(unsigned int driverClass, unsigned int index);
    static unsigned short getBladeRareIconID(unsigned int blade);  // 0 for none
    static unsigned short getBladeAttributeID(unsigned int blade);
    static bool isBladeSelectable(unsigned int blade, const GfMenuBladeList* list);
    // false while driver 4 is unused; isBladeSelectable asks it for blades 1005-1007
    static bool isAvailableTora();
    static bool isBladeReleasable(unsigned int blade, const GfMenuBladeList* list);
    static bool isBladeAchivementReleased(unsigned int blade);  // a bond line's achievement released at some level
    static unsigned int getBladeRank(unsigned int blade);
    static unsigned int getBladeRarity(unsigned int blade);
    static unsigned int getBladeCorrectiveType(unsigned int blade);  // 0 for none
    static unsigned int getBladeCorrectiveRatio(unsigned int blade);
    // the set (slot) of a driver's blade, -1 for none
    static int getSetBladeID(unsigned int driver, int slot, bool);
    // 2.0.0's symbols name it (their isBladeEnableOffset beside it takes a driver and an offset and calls
    // getSetBladeID; 3.0.1 has no such function). Whether the leader's blade can be used: always with add-on menu
    // layer 3 usable, else whether the first party member's driver has a set blade that is not a dummy
    static bool isLeaderBladeEnable();
    static unsigned int getBladeAttributeIconID(unsigned int blade);  // 0x9E plus the blade's attribute
    static bool isBladeDifferentImage(unsigned int blade, unsigned int other);  // their menu ids differ
    static bool isScenarioBlade(unsigned int blade);  // a regular blade or blade 1014
    // GfMenuObjBladeRelease::seqSubMenuOpen picks its seqSubMenuErrorOvdOnly / seqSubMenuErrorOvdLastOne jobs by
    // them (with a null list)
    static bool isBladeLastOneInSlot(unsigned int blade, const GfMenuBladeList* list);
    static bool isBladeLastOne(unsigned int blade, const GfMenuBladeList* list);
    // 0 when the blade can be removed, else why not (mode 1 also asks GfGameManager::isRexAwakening)
    static int canRemoveBladeEx(unsigned int blade, unsigned int mode,
                                const mm::mtl::FixedVector<unsigned short, 422>* list);
    static bool canRemoveBlade(unsigned int blade, const mm::mtl::FixedVector<unsigned short, 422>* list);
    static bool isCustomEnableDriver(unsigned int driver);
    // 2.0.0's symbols name it. Defined in gf_menu_obj_vision.cpp (the unit that owns its address; 2.0.0 places it
    // among GfMenuObjUtil's functions). What it does: false for blade 0x412, else true once the game is cleared or
    // GfDataUtil::getScenarioFlag() is past 2000 (GfMenuObjCharSelect::CharListener asks it).
    static bool isCustomEnableBlade(unsigned int blade);
    // whether the driver has Homura (blade 1001): its creator, and not unused
    static bool hasHomura(unsigned int driver);
    // the cursor's list becomes the handle's children that format names (from 1), or those of the names
    static void changeCursorTarget(ui::UICtrlCursorSelect* cursor, unsigned int handle, const char* format);
    static void changeCursorTarget(ui::UICtrlCursorSelect* cursor, unsigned int handle, const char** names,
                                   unsigned short count);
    // an enemy whose character property's flag at 0x30 is set (GfMenuGfObjAdapter::update_Battle reads it too)
    static bool isInBattle(gf::GF_OBJ_HANDLE* handle);
    // a driver's (type 3) or blade's (type 4) favorite: 2 when it has none (or for another type), 1 when it is not
    // used yet, 0 when it is
    // a follow-display plugin on the handle that follows the other object, and a sync plugin copying what flag
    // names from the target
    // how createDockPluginEx docks (the names follow the UIObjectDockPlugin fields they set; not the original's)
    struct DockingOption {
        int m_align;
        mm::Pnt<short> m_offset;
        mm::Rect<short> m_area;
    };
    // a dock plugin on the handle docking it to the target at a side (UIObjectDockPlugin::m_side)
    static void createDockPlugin(unsigned int handle, unsigned int target, unsigned int side,
                                 const mm::Pnt<short>& offset, unsigned int align);
    static void createDockPluginEx(unsigned int handle, unsigned int target, unsigned int side,
                                   const DockingOption& option);
    static void createFollowDispPlugin(unsigned int handle, unsigned int follow);
    static void createSyncPlugin(unsigned int handle, unsigned int target, unsigned int flag);
    static unsigned int getFavoriteStat(unsigned int type, unsigned int id, FAVORITE favorite);
    // the blades of the list that meet a mission's blade condition
    static unsigned int getMissionCondBladeCount(const GfRequestBladeData& data, const GfMenuBladeList* list);
    // the list's blades meet every blade condition of the mission
    static bool checkMissionCond(unsigned int mission, const GfMenuBladeList* list);
    // a mercenary mission's data as GfMenuObjMercenaryTop::updateMissionList shows it (getMissionInfo fills it from
    // GfDataMercenaries; the names are not the original's)
    struct MissionInfo {
        int m_category;                // getMissionCategory
        unsigned int m_reward;         // getMissionRewardID
        unsigned int m_map;            // getMissionMapID
        unsigned int m_flags;          // bit 0 new, bit 1/2/3 mission flag 1/2/3
        unsigned int m_team;           // getTeamIDByMissionID
        unsigned int m_fieldSkills[3]; // getFieldSkill1..3
    };
    // false for mission 0
    static bool getMissionInfo(unsigned int mission, MissionInfo& info);
};
}  // namespace gf

#endif

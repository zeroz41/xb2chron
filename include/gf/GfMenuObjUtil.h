#ifndef GF_GFMENUOBJUTIL_H
#define GF_GFMENUOBJUTIL_H

#include "classes/ui/UICtrlCursorSelect.h"

namespace gf { class GfMenuCallContext; }
namespace ui { class UIListInfoBase; }
namespace fw { enum SoundCategory : int; }
namespace ui { class UIStr; }

namespace gf {
// the menu objects' shared helpers; its functions take no object
class GfMenuObjUtil {
public:
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
        short m_pos[2];        // where bit 7's position method moves to
        float m_scale;         // added to the scale
        unsigned char pad_30[4];
        float m_rot;           // added to the rotation
        float m_bright;        // the brightness method's target
        float m_alpha;
        unsigned char pad_40[0x10];
        const char* m_motionLib;  // the motion method's library and motion
        const char* m_motion;
    };
    // what startPresetCtrl turns into a CtrlParam: one of its preset fades, in or out
    struct PresetCtrlParam {
        // m_startFlag4 is the callers' (GfMenuObjEnvironmentInfo's and GfMenuObjSpecialGauge's set it), and the
        // order of the stores is the original's
        PresetCtrlParam() : m_slot(-1), m_startFlag1(false), m_startFlag4(false), m_eventId(0), m_delay(0.0f), m_child(nullptr) {
            m_preset = 0;
            m_out = 0;
        }
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
    static bool getMenuCondition(unsigned int condition);  // whether a menu's condition is met
    static bool checkCCStart(GfMenuCallContext* context);  // a context that is not running yet
    static bool checkCCNext(GfMenuCallContext* context, unsigned int id);  // a context running on that id
    static void setDockPos(unsigned int handle, unsigned int target, unsigned char pos, bool);
    static void addPos(unsigned int handle, short x, short y);
    // the slot of the control it starts on the handle (or its child of that name), -1 for none
    static int startCtrl(unsigned int handle, const CtrlParam& param, const char* child);
    static int getCtrlID(unsigned int handle);  // the slot of the control running on the handle, -1 for none
    static void stopCtrl(int slot);  // nothing for -1
    static bool isBusyCtrl(int slot);
    static void playSE(unsigned int se);
    static int startPresetCtrl(unsigned int handle, const PresetCtrlParam& param);  // startCtrl's slot
    static short getBtnIconNumber(unsigned int button);  // the icon number of a button
    static unsigned int playBGM(unsigned int bgm, bool, fw::SoundCategory category);  // the handle stopBGM takes
    static void stopBGM(unsigned int handle, float time);
    static bool isValidBlade(unsigned int blade);
    static void playSECommonFromInput(unsigned int input);  // the common sound for a menu input
    static void playSECommonCursor();  // the common sound of a cursor move
    static void playSECommon(unsigned int se);  // one of the common menu sounds
    static void playSECommonDecide();
    static void playSECommonCancel();
    static void setChildDisp(unsigned int handle, const char* child, bool disp);  // its child of that name
    static void setChildIcon(unsigned int handle, const char* child, unsigned short icon);
    static void playJingle(unsigned int jingle);
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
    // a combo's effect text, and its effect (3.0.1's always 1) (GfMenuElementComboAdapter's update_*)
    static ui::UIStr getElementComboEffectName(unsigned int combo);
    static unsigned char getElementComboEffect(unsigned int combo);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in this
    // file, which holds only GfMenuObjUtil's functions (1.0.0: 159 of 159). What it does: whether the add-on menu
    // layer `layer` is usable. False unless bit `layer` of UIStr.cpp's layer mask (lbl_7100B75878; fn_7100696950
    // sets a bit, fn_7100696970 tests one, fn_7100696A28 opens a set layer's "MNU_Layer_Dlc%02d" BDAT) is set;
    // then layer 3 is GfGameManager::fn_71002A9E68, layer 2 is always usable, layer 1 is fn_71002AC598 (add-on
    // content 0x01010003, checked by gf_game_env.cpp's fn_71002A75DC), any other layer is not. GfMenuManager's
    // constructor sets bit 1 when fn_71002AC598 holds, and bit 3 when "menu_ira/font/bf2.wisty" is present (it then
    // gives UIStr the font folder "menu_ira") or add-on content 0x101 is owned. 344 functions call it: 3 at 427 call sites
    // and 1 at 46.
    static bool fn_710048FD30(unsigned int layer);
};
}  // namespace gf

#endif

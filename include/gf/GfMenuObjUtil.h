#ifndef GF_GFMENUOBJUTIL_H
#define GF_GFMENUOBJUTIL_H

namespace gf { class GfMenuCallContext; }
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
        PresetCtrlParam() : m_slot(-1), m_startFlag1(false), m_eventId(0), m_delay(0.0f), m_child(nullptr) {
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
    static void setColDefault(unsigned int handle);  // the object's default colours back
    static void setColMulandAdd(unsigned int handle, const char* name);  // the colours of a named preset
    // an elemental combo's attribute and name, from its BDAT row (attribute 0 for an invalid one)
    static unsigned char getElementComboAtr(unsigned int combo);
    static ui::UIStr getElementComboName(unsigned int combo);
};
}  // namespace gf

#endif

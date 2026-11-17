#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GfMenuBladeList; }
namespace gf { class GfMenuCallContext; }
namespace gf { class GfMenuIDList; }
namespace gf { class GfMenuReferenceNumber; }
namespace gf { class GAME_VOICE_HANDLE; }
namespace mm { namespace mtl { class ReferenceObject; } }
namespace ui { class UICtrlCursorSelect; }
namespace ui { class UISelectObjList; }

namespace gf {
// table 0x7100B63350
// The layout is from the constructor, the destructor (which releases every list, cursor and context it holds) and
// initialize; the field names are not the original's.
class GfMenuObjMercenaryForm : public ::gf::GfMenuObject {
public:
    class ApplyListener;
    class BlImgListener;
    class FormListener;
    class LeaderListener;
    class ListListener;
    class MainListener;
    class PresetListener;
    class StartListener;
    class UnitListener;
    GfMenuObjMercenaryForm(unsigned int handle);
    virtual ~GfMenuObjMercenaryForm();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // its sequence's jobs (1.0.0's names)
    bool seqLeaveBlade();
    bool seqReturnMissionSelect();
    bool seqPresetSave();
    bool seqPresetLoad();
    bool seqConfirmStart();
    bool seqOpenImage();
    bool seqDepartureStart();
    bool seqApperBlade();
    bool seqDepartureEnd();
    // 2.0.0's (names from its symbols, where they follow seqDepartureEnd); 3.0.1's linker dropped them as unused,
    // leaving their strings in gf_menu_obj_mercenary_form's .rodata. Each queues the next: seqStartActiveFS shows
    // LAY_start_fs, seqOpenActiveFS plays IMG_start_fs_base's result, seqDispActiveFS its fade_in_info and a wait,
    // seqEndActiveFS hides LAY_start_fs and queues seqLeaveBlade
    bool seqStartActiveFS();
    bool seqOpenActiveFS();
    bool seqDispActiveFS();
    bool seqEndActiveFS();
    bool seqPresetEnd();
    bool seqRevertBladeSet();
    // 2.0.0's symbols name them. Their code reads the form's lists and sequence state and sits among the class's
    // functions. whether the blade is already in the team list (m_unitBlades), or both it and a member are one of
    // GfMenuObjUtil::isBladeHana's blades; caller seqConfirmHana
    bool chkUnitBladeList(unsigned int blade);
    // inline in 3.0.1 (2.0.0 names both and keeps them out of line); ListListener calls them. updateReserveBlade:
    // makes the blade list's blade at that index the reference blade, recounts the conditions with it added and
    // redraws the list. chkTempUnlink: whether the blade is in m_bladeIds
    void updateReserveBlade(unsigned int index);
    bool chkTempUnlink(unsigned int blade);
    // m_seq job (ListListener adds it): asks common window 0x10F and, on yes, adds the blade list's selected blade
    // to the team list (with its creator) unless chkUnitBladeList holds, then reopens LAY_form_list_bl
    bool seqConfirmHana();
    // m_seq job (ListListener adds it): asks common window 199 (0x10F for isBladeHana's blades) and, on yes,
    // puts the blade list's selected blade into m_bladeIds (once) and then into the team list as seqConfirmHana does
    bool seqConfirmRemoveBladeSet();
    void setDetailBladePos(unsigned int index);
    void updateBladeCount(bool, bool);
    void refreshBladeList();
    // inline in 3.0.1 (2.0.0 names both and keeps them out of line): sends an open event (0x21) with that first
    // parameter to the handle's object, or to LAY_form_main when the handle is 0 (the Form listener's events 3 and
    // 0x103)
    void sendOpenEvent(unsigned int handle, int param, float delay);
    // the same with a close event (0x22) (seqDepartureEnd's LAY_start, seqPresetEnd's LAY_preset); 2.0.0's copy
    // stores the parameter as the open one does
    void sendCloseEvent(unsigned int handle, int param, float delay);

    unsigned int m_teamId;                    // 0x24: GfMenuReference::getReferenceTeamID's
    GfMenuBladeList* m_unitBlades;            // 0x28: the team's blades (initialize)
    GfMenuBladeList* m_listBlades;            // 0x30: the blade list's (initialize; its scroll bar's list)
    GfMenuBladeList* m_presetBlades[3];       // 0x38: initialize creates three more lists
    GfMenuBladeList* m_presetLists[3];        // 0x50: initialize creates them; seqPresetSave fills the one of
                                              // m_idList's index
    GfMenuIDList* m_idList;                   // 0x68
    unsigned int pad_70[2];
    ui::UISelectObjList* m_unitSelect;        // 0x78: on "LAY_form_unit_bl"
    ui::UICtrlCursorSelect* m_unitCursor;     // 0x80: "IMG_form_unit_bl_cursor"
    ui::UISelectObjList* m_formSelect;        // 0x88
    ui::UICtrlCursorSelect* m_formCursor;     // 0x90
    ui::UISelectObjList* m_listSelect;        // 0x98: on "LAY_form_list_bl"
    ui::UICtrlCursorSelect* m_listCursor;     // 0xA0
    ui::UISelectObjList* m_presetSelect;      // 0xA8: on "LAY_preset"
    ui::UICtrlCursorSelect* m_presetCursor;   // 0xB0
    GfMenuCallContext* m_context;             // 0xB8
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numbers[8];  // 0xC0
    unsigned int pad_100;
    unsigned int m_waitFrames;                // 0x104: update counts it down
    GfMenuSequence<GfMenuObjMercenaryForm, 10> m_seq;    // 0x108
    bool m_seqStep;                           // 0x430: a job's first step done (seqRevertBladeSet: the window is open)
    GfMenuSequence<GfMenuObjMercenaryForm, 4> m_subSeq;  // 0x438
    // 0x598: refreshBladeList searches it, seqConfirmRemoveBladeSet adds to it (its push_back's capacity check is 422, as
    // GfMenuBladeList's FixedVector<unsigned short, 422> lists)
    mm::mtl::FixedVector<unsigned short, 422> m_bladeIds;
    bool pad_8F0;
    GAME_VOICE_HANDLE* m_voice;               // 0x8F8: seqApperBlade stops it
    long m_leaveVoice;                        // 0x900: -1 for none; update and seqLeaveBlade stop it
    bool m_leaveRequest;                      // 0x908: update queues seqLeaveBlade with it
    bool m_voiceStopped;                      // 0x909: seqApperBlade sets it as it stops m_voice
};
}  // namespace gf

#endif

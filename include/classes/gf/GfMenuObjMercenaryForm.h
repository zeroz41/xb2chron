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
    bool seqPresetEnd();
    bool seqRevertBladeSet();
    void setDetailBladePos(unsigned int index);
    void updateBladeCount(bool, bool);
    void refreshBladeList();

    unsigned int m_teamId;                    // 0x24: GfMenuReference::getReferenceTeamID's
    GfMenuBladeList* m_unitBlades;            // 0x28: the team's blades (initialize)
    GfMenuBladeList* m_listBlades;            // 0x30: the blade list's (initialize; its scroll bar's list)
    GfMenuBladeList* m_presetBlades[3];       // 0x38: initialize creates three more lists
    mm::mtl::ReferenceObject* m_refs[3];      // 0x50: only the destructor releases them here
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
    mm::mtl::FixedVector<unsigned short, 424> m_bladeIds;  // 0x598: refreshBladeList searches it
    bool pad_8F0;
    GAME_VOICE_HANDLE* m_voice;               // 0x8F8: seqApperBlade stops it
    long m_leaveVoice;                        // 0x900: -1 for none; update and seqLeaveBlade stop it
    bool m_leaveRequest;                      // 0x908: update queues seqLeaveBlade with it
    bool m_voiceStopped;                      // 0x909: seqApperBlade sets it as it stops m_voice
};
}  // namespace gf

#endif
